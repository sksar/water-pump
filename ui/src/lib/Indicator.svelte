<script>
    let {
        active = $bindable(false)
    } = $props();
</script>

<section class="flex flex-col items-center gap-2">
    <!-- Braun-style Minimal Indicator -->
    <div class="relative w-12 h-12 flex items-center justify-center">
        <!-- Minimal Flat Housing -->
        <div class="absolute inset-0 rounded-full bg-[#E0E0E0] shadow-[0_2px_4px_rgba(0,0,0,0.1),inset_0_1px_1px_rgba(255,255,255,0.7)] border border-[#CBCBCB]"></div>
        
        <!-- Minimal Orange Indicator Dot -->
        <div class="relative w-6 h-6 rounded-full transition-all duration-300 ease-in-out
            {active 
                ? 'bg-[#FF7F00] shadow-[0_0_12px_rgba(255,127,0,0.5),inset_0_1px_2px_rgba(255,255,255,0.4)] animate-pulse'
                : 'bg-[#B0B0B0] shadow-[inset_0_1px_1px_rgba(0,0,0,0.2)]'
            }">
        </div>
    </div>

    <!-- Indicator Text -->
    <div
        class="text-[10px] uppercase tracking-[0.15em] font-bold {active ? 'text-[#FF7F00]' : 'text-[#999]'} transition-colors duration-300">
        {active ? 'Pumping' : 'Idle'}
    </div>
</section>

