<script>
    import { pump, rpc } from "$lib/pump";
    import { buttonSound } from "$lib/sounds";

    import Dial from "$lib/Dial.svelte";
    import Button from "$lib/Button.svelte";
    import Indicator from "$lib/Indicator.svelte";

    let minutes = $state(0);
    let active = $derived($pump?.['ttl'] > 0);

    $effect(() => {
        if (active) minutes = Math.ceil($pump?.['ttl'] / 60);
        else minutes = 0;
    });

    function stop() {
        rpc("stop");
        buttonSound();
    }

    function start() {
        rpc("start", { minutes });
        buttonSound();
    }
</script>

<main class="h-screen bg-[#F0F0F0] flex flex-col items-center justify-between p-8 select-none overflow-hidden">

    <!-- Header Area -->
    <header class="w-full flex justify-between items-start">
        <h1 class="text-[13px] font-bold tracking-widest text-[#222] uppercase">Water Pump</h1>
        <p class="text-[10px] tracking-widest text-[#888] uppercase mt-0.5">Control Panel</p>
    </header>

    <!-- Main Control Area -->
    <section class="flex-1 flex flex-col items-center justify-evenly w-full max-w-lg">

        <!-- LED Indicator -->
        <Indicator {active} />

        <!-- Timer Dial -->
        <Dial bind:value={minutes} max={30} {active} />

        <!-- Push Buttons -->
        <div class="flex items-center gap-20">
            <Button label="Start" variant="green" onclick={start} disabled={active || minutes === 0} />
            <Button label="Stop" variant="red" onclick={stop} />
        </div>

    </section>
</main>

<style>
    :global(body) {
        background-color: #F0F0F0;
        color: #222;
    }
</style>


