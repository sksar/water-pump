let audioCtx;

function getAudioContext() {
    if (!audioCtx) audioCtx = new window.AudioContext();
    return audioCtx;
}

/**
 * Simulates a mechanical, metallic click sound.
 */
export function metalSound(volume = 1, pitch = 1) {

    const ctx = getAudioContext();
    if (ctx.state === 'suspended') ctx.resume();
    const time = ctx.currentTime;

    // 1. High-frequency noise burst (the "snap")
    const noiseBuffer = ctx.createBuffer(1, ctx.sampleRate * 0.05, ctx.sampleRate);
    const output = noiseBuffer.getChannelData(0);
    for (let i = 0; i < noiseBuffer.length; i++) {
        output[i] = Math.random() * 2 - 1;
    }

    const noise = ctx.createBufferSource();
    noise.buffer = noiseBuffer;

    const noiseFilter = ctx.createBiquadFilter();
    noiseFilter.type = 'highpass';
    noiseFilter.frequency.setValueAtTime(2500 * pitch, time);

    const noiseGain = ctx.createGain();
    noiseGain.gain.setValueAtTime(0.15 * volume, time);
    noiseGain.gain.exponentialRampToValueAtTime(0.001, time + 0.01);

    noise.connect(noiseFilter);
    noiseFilter.connect(noiseGain);
    noiseGain.connect(ctx.destination);

    // 2. Metallic "Ping" (resonant high frequency)
    const ping = ctx.createOscillator();
    ping.type = 'sine';
    ping.frequency.setValueAtTime(4000 * pitch, time);

    const pingGain = ctx.createGain();
    pingGain.gain.setValueAtTime(0.05 * volume, time);
    pingGain.gain.exponentialRampToValueAtTime(0.001, time + 0.03);

    ping.connect(pingGain);
    pingGain.connect(ctx.destination);

    // 3. Low-frequency "Thud" (mechanical body)
    const thud = ctx.createOscillator();
    thud.type = 'triangle';
    thud.frequency.setValueAtTime(150 * pitch, time);

    const thudGain = ctx.createGain();
    thudGain.gain.setValueAtTime(0.1 * volume, time);
    thudGain.gain.exponentialRampToValueAtTime(0.001, time + 0.02);

    thud.connect(thudGain);
    thudGain.connect(ctx.destination);

    noise.start(time);
    ping.start(time);
    thud.start(time);

    ping.stop(time + 0.05);
    thud.stop(time + 0.05);
}


export function buttonSound() {
    metalSound(1.0, 0.8);
}

export function tickSound() {
    metalSound(0.4, 1.5);
}
