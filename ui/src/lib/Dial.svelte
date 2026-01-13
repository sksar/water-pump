<script>
    import { tickSound } from "$lib/sounds";

    let {
        value = $bindable(0),
        max = $bindable(30),
        active = $bindable(false),
    } = $props();

    let dialElement = $state();
    let rotation = $derived((value / max) * 360);

    let dragging = $state(false);

    function handleStart(e) {
        if (e.type === 'touchstart') e?.preventDefault();
        dragging = true;
        update(e);
    }

    function handleEnd() {
        dragging = false;
    }

    function handleMove(e) {
        if (!dragging) return;
        update(e);
    }

    function update(e) {
        if (active) return;

        const box = dialElement.getBoundingClientRect();
        const cx = box.left + box.width / 2;
        const cy = box.top + box.height / 2;

        const touch = e.touches?.[0] || e;
        const dx = touch.clientX - cx;
        const dy = touch.clientY - cy;

        let angle = Math.atan2(dy, dx) * (180 / Math.PI);
        angle = (angle + 90 + 360) % 360; // Offset by 90
        value = Math.round((angle / 360) * max);
    }

    $effect(() => {
        value;
        tickSound();
    });
</script>

<svelte:window onmousemove={handleMove} onmouseup={handleEnd} ontouchmove={handleMove} ontouchend={handleEnd}/>

<div role="button" tabindex="0"
     class="relative w-64 h-64 flex items-center justify-center select-none touch-none"
     bind:this={dialElement}
     onmousedown={handleStart}
     ontouchstart={handleStart}
>
    <!-- Outer Plate: Braun-style off-white -->
    <div id="outer-plate"></div>

    <!-- Ticks -->
    <svg viewBox="0 0 100 100" class="absolute inset-0 w-full h-full p-6">
        <g transform="translate(50, 50)">
            {#each Array.from({length: max}) as _, i}
                {@const big = i % 5 === 0}
                <g transform={`rotate(${i * 360 / max})`}>
                    <line x1="0" y1="-41" stroke={big ? "#333" : "#999"} stroke-width={big ? "0.6" : "0.3"} />
                    {#if big}
                        <text x="0" y="-44" class="tracking-wide font-bold text-[8px] [text-anchor:middle]">{i}</text>
                    {/if}
                </g>
            {/each}
        </g>
    </svg>

    <!-- Main Knob -->
    <div id="knob">

        <!-- Ribs (Rotating) -->
        <div style="transform: rotate({rotation}deg)" class="rotating-area opacity-15">
            <svg viewBox="0 0 100 100" class="w-full h-full">
                {#each Array(72) as _, i}
                    <line x1="50" y1="50" x2="0" y2="0" transform="rotate({i * 5} 50 50)" stroke="black"
                          stroke-width="0.5"/>
                {/each}
            </svg>
        </div>

        <!-- Inner Area (Fixed) -->
        <div
            class="absolute inset-2 rounded-full bg-linear-to-b from-[#F5F5F5] to-[#E5E5E5] shadow-[inset_0_2px_4px_rgba(0,0,0,0.1),0_1px_2px_rgba(255,255,255,0.8)]"></div>

        <!-- Indicator Dot (Rotating) -->
        <div style="transform: rotate({rotation}deg)" class="rotating-area">
            <div style="transform: rotate(-{rotation}deg)"
                 class="absolute top-4 w-3 h-3 rounded-full bg-[#D12C2C] shadow-[0_1px_2px_rgba(0,0,0,0.4),inset_0_1px_1px_rgba(255,255,255,0.4)] z-10 transition-transform duration-200 left-1/2 -ml-1.5"></div>
        </div>
    </div>

    <!-- Value -->
    <div class="absolute pointer-events-none flex flex-col items-center z-20 -mt-1">
        <span class="text-[36px] font-medium text-[#222] tracking-tighter tabular-nums">
            {value}
        </span>
        <span class="text-[9px] uppercase tracking-[0.2em] text-[#AAA] font-bold -mt-1.5">
            min {active ? "left" : ""}
        </span>
    </div>
</div>

<style lang="postcss">
    @import "tailwindcss";

    .rotating-area {
        @apply absolute inset-0 transition-transform duration-200;
        @apply transition-transform duration-200;
    }

    #outer-plate {
        @apply absolute inset-0 rounded-full bg-[#E0E0E0] border border-[#CBCBCB];
        @apply shadow-[0_12px_24px_rgba(0,0,0,0.2),inset_0_2px_5px_rgba(255,255,255,0.8),inset_0_-2px_5px_rgba(0,0,0,0.1)];
    }

    #knob {
        @apply overflow-hidden relative w-40 h-40 rounded-full bg-[#EEEEEE];
        @apply shadow-[0_20px_40px_-10px_rgba(0,0,0,0.3),0_8px_16px_rgba(0,0,0,0.1),inset_0_1px_1px_rgba(255,255,255,1),inset_0_-1px_1px_rgba(0,0,0,0.15)];
    }
</style>
