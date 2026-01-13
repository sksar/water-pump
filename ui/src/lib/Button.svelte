<script>
    let { 
        label = "", 
        variant = "default", 
        onclick = () => {}, 
        disabled = false 
    } = $props();

    // Dieter Rams inspired themes
    const themes = {
        green: {
            base: "bg-[#1A1A1A]",
            cap: "from-[#4B8B4B] to-[#3D743D]",
            rim: "border-[#5A9B5A]/30",
            label: "text-[#2A2A2A]"
        },
        red: {
            base: "bg-[#1A1A1A]",
            cap: "from-[#C43E3E] to-[#A82222]",
            rim: "border-[#D15E5E]/30",
            label: "text-[#2A2A2A]"
        },
        default: {
            base: "bg-[#111111]", // High contrast black rim from image
            cap: "from-[#FFFFFF] to-[#F5F5F5]",
            rim: "border-black/5",
            label: "text-[#444]"
        }
    };

    const t = $derived(themes[variant] || themes.default);
</script>

<div class="flex flex-col items-center gap-5">
    <!-- Button Housing (The Black Bezel) -->
    <div class="
        relative w-16 h-16 sm:w-20 sm:h-20 rounded-full 
        {t.base} flex items-center justify-center p-0.5
        shadow-[0_20px_40px_-10px_rgba(0,0,0,0.4),0_10px_20px_-10px_rgba(0,0,0,0.3)]
        before:absolute before:inset-0 before:rounded-full before:shadow-[inset_0_1px_1px_rgba(255,255,255,0.15)]
    ">
        <!-- Inner Well -->
        <div class="w-full h-full rounded-full bg-black/40 shadow-[inset_0_2px_6px_rgba(0,0,0,0.6)] flex items-center justify-center p-[1px]">
            
            <!-- Mechanical Button Cap -->
            <button
                {onclick}
                {disabled}
                class="
                    relative w-full h-full rounded-full transition-all duration-150 ease-out
                    bg-linear-to-br {t.cap}
                    {t.rim} border-[0.5px]
                    shadow-[
                        0_6px_10px_rgba(0,0,0,0.4),
                        0_2px_4px_rgba(0,0,0,0.2),
                        inset_0_2px_2px_rgba(255,255,255,1),
                        inset_0_-2px_4px_rgba(0,0,0,0.1)
                    ]
                    active:translate-y-1
                    active:shadow-[
                        inset_0_4px_8px_rgba(0,0,0,0.3),
                        0_1px_2px_rgba(0,0,0,0.2)
                    ]
                    disabled:opacity-50 disabled:grayscale disabled:cursor-not-allowed
                    flex items-center justify-center
                    outline-none group
                "
            >
                <!-- Surface curvature highlight -->
                <span class="absolute inset-0 rounded-full bg-linear-to-tr from-transparent via-white/5 to-white/20 pointer-events-none"></span>
                
                <!-- Internal tactile shadow -->
                <span class="absolute inset-0 rounded-full shadow-[inset_0_1px_1px_rgba(255,255,255,0.5),inset_0_-1px_1px_rgba(0,0,0,0.1)] pointer-events-none"></span>
            </button>
        </div>
    </div>
    
    <!-- Label -->
    {#if label}
        <span class="text-[10px] font-black tracking-[0.3em] text-[#333] uppercase select-none">
            {label}
        </span>
    {/if}
</div>

<style>
    button {
        -webkit-tap-highlight-color: transparent;
        cursor: pointer;
    }
    
    button:disabled {
        cursor: not-allowed;
    }
</style>
