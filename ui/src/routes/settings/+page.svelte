<script>
    import { rpc } from "$lib/pump";
    import { goto } from "$app/navigation";
    import { onMount } from "svelte";

    let cronTime = $state("05:00");
    let loading = $state(true);
    let saving = $state(false);

    let config = $state({
        app: {
            cron_start: {
                enable: false,
                expr: "",
                duration: 5
            },
            telegram_chat_id: 0
        },
        telegram: {
            enable: false,
            token: ""
        }
    });

    // Generate intervals
    const timeOptions = [];
    for (let h = 0; h < 24; h++) {
        for (let m = 0; m < 60; m += 30) {
            const hh = h.toString().padStart(2, '0');
            const mm = m.toString().padStart(2, '0');
            timeOptions.push(`${hh}:${mm}`);
        }
    }

    async function getConfig() {
        try {
            config = await rpc("Config.Get");

            // cron format: "0 0 5 * * *" -> "05:00"
            const parts = config.app.cron_start.expr.split(" ");
            if (parts.length >= 3) {
                const hh = parts[2].padStart(2, '0');
                const mm = parts[1].padStart(2, '0');
                cronTime = `${hh}:${mm}`;
            }

            loading = false;
        } catch (e) {
            setTimeout(getConfig, 2000);
        }
    }

    onMount(getConfig);

    async function save() {
        saving = true;
        try {
            // cron format: "sec min hr * * *"
            const [hh, mm] = cronTime.split(":").map(s => parseInt(s, 10));
            config.app.cron_start.expr = `50 ${mm} ${hh} * * *`;
            
            // Only send the parts we want to update to avoid payload size issues on ESP8266
            await rpc("Config.Set", {
                config: {
                    app: config.app,
                    telegram: config.telegram,
                    sys: { tz_spec: getPosixTz() },
                }
            });
            
            await rpc("Config.Save", { reboot: true });
            alert("Settings saved");
        } catch (e) {
            console.error("Failed to save config", e);
            alert("Failed to save settings");
        } finally {
            saving = false;
        }
    }

    function getPosixTz() {
        const offset = new Date().getTimezoneOffset(); // e.g., -330 for India
        const absOffset = Math.abs(offset);
        const h = Math.floor(absOffset / 60);
        const m = absOffset % 60;
        const sign = offset > 0 ? "" : "-";
        return `GMT${sign}${h}:${m.toString().padStart(2, '0')}`;
    }
</script>

<main class="h-screen flex flex-col overflow-scroll">

    <header class="px-8 py-4 bg-zinc-100 border-b border-zinc-300 flex justify-between items-start">
        <h1 class="text-[13px] font-bold tracking-widest text-[#222] uppercase">Water Pump Settings</h1>
        <button class="text-[10px] tracking-widest text-[#888] uppercase mt-0.5" onclick={() => goto('/')}>Back</button>
    </header>

    <section class="max-w-lg w-full mx-auto p-8 overflow-scroll">
        {#if loading}
            <p class="text-center text-zinc-500">Loading...</p>
        {:else}
            <div class="space-y-6">

                <article>
                    <h2>Auto Start Settings</h2>

                    <div class="flex items-center gap-3 mb-4">
                        <input type="checkbox" id="auto-start-enabled" bind:checked={config.app.cron_start.enable}/>
                        <label for="auto-start-enabled" class="text-sm">Enabled</label>
                    </div>

                    <div class="space-y-4">
                        <div>
                            <label for="auto-start-time"
                                   class="block text-[10px] uppercase tracking-wider text-zinc-500 mb-1">Start Time
                                (24h)</label>
                            <select id="auto-start-time" bind:value={cronTime}
                                    class="w-full px-2 py-1 border border-zinc-300 rounded-md bg-white">
                                {#each timeOptions as time}
                                    <option value={time}>{time}</option>
                                {/each}
                            </select>
                        </div>

                        <div>
                            <label for="auto-start-duration"
                                   class="block text-[10px] uppercase tracking-wider text-zinc-500 mb-1">Duration
                                (minutes)</label>
                            <select id="auto-start-duration" bind:value={config.app.cron_start.duration}
                                    class="w-full px-2 py-1 border border-zinc-300 rounded-md bg-white">
                                {#each Array.from({length: 60}, (_, i) => i + 1) as minutes}
                                    <option value={minutes}>{minutes} Minutes</option>
                                {/each}
                            </select>
                        </div>
                    </div>
                </article>

                <article>
                    <h2>Telegram Notifications</h2>

                    <div class="flex items-center gap-3 mb-4">
                        <input type="checkbox" id="tg-enabled" bind:checked={config.telegram.enable}/>
                        <label for="tg-enabled" class="text-sm">Enabled</label>
                    </div>

                    <div class="space-y-4">
                        <div>
                            <label for="tg-token" class="block text-[10px] uppercase tracking-wider text-zinc-500 mb-1">Bot
                                Token</label>
                            <input type="text" id="tg-token" bind:value={config.telegram.token}
                                   placeholder="123456:ABC-DEF..."/>
                        </div>

                        <div>
                            <label for="tg-chat-id"
                                   class="block text-[10px] uppercase tracking-wider text-zinc-500 mb-1">Chat ID</label>
                            <input type="number" id="tg-chat-id" bind:value={config.app.telegram_chat_id}/>
                        </div>
                    </div>
                </article>

                <button
                    class="w-full bg-zinc-800 text-white py-2 rounded-md text-[11px] uppercase tracking-widest font-bold disabled:opacity-50"
                    onclick={save}
                    disabled={saving}
                >
                    {saving ? 'Saving...' : 'Save Settings'}
                </button>
            </div>

        {/if}
    </section>

</main>


<style lang="postcss">
    @import "tailwindcss";

    input[type="number"], input[type="text"] {
        @apply w-full px-2 py-1 border border-zinc-300 rounded-md;
    }

    input[type="checkbox"] {
        @apply w-4 h-4 rounded-sm border border-zinc-300;
    }

    h2 {
        @apply text-[13px] font-medium tracking-widest text-[#222] uppercase mb-4;
    }
</style>