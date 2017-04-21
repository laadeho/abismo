s.options.device_("ASIO : ASIO4ALL v2");
s.boot;
s.meter;
Server.default.makeGui;
s.recChannels_(4); // or whatever number of channels
s.record;
stop.record;

c = 4;
s.options.numOutputBusChannels = c;
s.options.sampleRate = 48000;
s.boot;
s.recChannels = c;
s.recHeaderFormat = "WAV";



///// MIEDO 00


~p00_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Miedo/P00.wav");
~p01_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Miedo/P01.wav");
~p02_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Miedo/P02.wav");
~p03_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Miedo/P03.wav");
~p04_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Miedo/P04.wav");
~p05_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Miedo/P05.wav");
~bajobeat_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Miedo/bajobeat_4ch.wav");
~grito_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Miedo/grito00_4ch.wav");


(
SynthDef(\p00, {| senal, paneo, out, env, gate = 1, salida, dir = 0.75, efecto, mix = 2, room = 2, damp = 2|
	senal = PlayBuf.ar(~p00_buf.numChannels, ~p00_buf.bufnum, dir, loop:0, doneaction:0)*6;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.5, 1, 0.5, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~p00 = Synth(\p00);


(
SynthDef(\p01, {| senal, paneo, out, env, gate = 1, salida, dir = 0.75, efecto, mix = 2, room = 2, damp = 2|
	senal = PlayBuf.ar(~p01_buf.numChannels, ~p01_buf.bufnum, dir, loop:0, doneaction:0)*6;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.5, 1, 0.5, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	Out.ar(1, Pan4.ar(salida,paneo,1));
}).add;
)

~p01 = Synth(\p01);


(
SynthDef(\p02, {| senal, paneo, out, env, gate = 1, salida, dir = 0.75, efecto, mix = 2, room = 2, damp = 2|
	senal = PlayBuf.ar(~p02_buf.numChannels, ~p02_buf.bufnum, dir, loop:0, doneaction:0)*6;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.5, 1, 0.5, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	Out.ar(2, Pan4.ar(salida,paneo,1));
}).add;
)

~p02 = Synth(\p02);


(
SynthDef(\p03, {| senal, paneo, out, env, gate = 1, salida, dir = 0.75, efecto, mix = 2, room = 2, damp = 2|
	senal = PlayBuf.ar(~p03_buf.numChannels, ~p03_buf.bufnum, dir, loop:0, doneaction:0)*6;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.5, 1, 0.5, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	Out.ar(3, Pan4.ar(salida,paneo,1));
}).add;
)

~p03 = Synth(\p03);


(
SynthDef(\p04, {| senal, paneo, out, env, gate = 1, salida, dir = 0.75, efecto, mix = 2, room = 2, damp = 2|
	senal = PlayBuf.ar(~p04_buf.numChannels, ~p04_buf.bufnum, dir, loop:0, doneaction:0)*6;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.5, 1, 0.5, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	Out.ar(1, Pan4.ar(salida,paneo,1));
}).add;
)

~p04 = Synth(\p04);


(
SynthDef(\p05, {| senal, paneo, out, env, gate = 1, salida, dir = 0.75, efecto, mix = 2, room = 2, damp = 2|
	senal = PlayBuf.ar(~p05_buf.numChannels, ~p05_buf.bufnum, dir, loop:0, doneaction:0)*6;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.5, 1, 0.5, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	Out.ar(2, Pan4.ar(salida,paneo,1));
}).add;
)

~p05 = Synth(\p05);


(
SynthDef(\bass, {| dur = 0.15, atk = 0.5, amp = 0.6, senal, salida |
	senal = SinOsc.ar(EnvGen.ar( Env(NamedControl.kr(\freq_l, [2960, 70, 90]),NamedControl.kr(\freq_d, [0.07, 0.2]),NamedControl.kr(\freq_c, [-13, -1]),) ),mul:amp * EnvGen.ar(Env.perc( atk, dur - atk, curve: NamedControl.kr(\amp_c, [-1, 6])),doneAction: 2);)!4;
	//env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.5, 1, 0.5, -4, 0), gate, doneAction:2);
	//efecto = FreeVerb.ar(senal, mix, room, damp);
	//salida = senal*env;
	Out.ar(0,senal);
}).add;
)

~bass = Synth(\bass);


(
SynthDef(\bass0, { | atk = 0.01, dur = 1, freq = 50, amp=0.6, senal, salida |
	senal = BPF.ar(LFSaw.ar(freq), freq, 2, mul: EnvGen.kr( Env.perc( atk, dur-atk, amp, 6 ), doneAction: 2 )) ! 4;
	//env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.5, 1, 0.5, -4, 0), gate, doneAction:2);
	//efecto = FreeVerb.ar(senal, mix, room, damp);
	//salida = senal*env;
	Out.ar(0,senal);
}).add;
)

~bass0 = Synth(\bass0);

(
Tdef(\bass, {
	10.do{
		~bass = Synth(\bass);
		2.wait;
		~bass0 = Synth(\bass0);
		1.wait;
		~bass = Synth(\bass);
		1.wait;
		~bass0 = Synth(\bass0);
		2.wait;
	};
};
);
)

Tdef(\bass).play;

Tdef(\bass).stop;



(
SynthDef(\bandpass5, {| saw, pan, out, xpos = 1, ypos = 1, frec = 10, freq1 = 1, freq2 = 4, range1 = 10, range2 = 100 env, gate = 1, salida, bpf|
	var lfn1 = LFNoise2.kr(freq1), lfn2 = LFNoise2.kr(freq2);
	saw = Saw.ar( frec, mul: LFPulse.kr(freq: LFNoise1.kr(freq1).range(range1, range2), width: 0.01))*3;
	bpf = BPF.ar(in: saw, freq: lfn1.range(700, 2500), rq: 1, mul: 1);
	//env = EnvGen.ar(Env([0,1],[5]));
	//salida = bpf*env;
	//salida = bpf*EnvGen.ar(Env.cutoff(1), gate, doneAction:2);
	pan = Pan4.ar(in: bpf, xpos: lfn1, ypos: lfn2);
	Out.ar(0, pan);
}).add;
)

~bandpass5 = Synth(\bandpass5)
~bandpass.set(\freq1, 1)
~bandpass.set(\freq2, 1)
~bandpass.set(\gate, 0);


(
SynthDef(\grito, {| senal, paneo, out, env, gate = 1, salida, dir = 0.9, efecto, mix = 2, room = 2, damp = 2|
	senal = PlayBuf.ar(~grito_buf.numChannels, ~grito_buf.bufnum, dir, loop:0, doneaction:0)*2;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.8, 0.1, 1, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal+efecto;
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~grito = Synth(\grito);
~grito.set(\gate, 0);


(
SynthDef(\sine, {| senal, paneo, out, env, gate = 1, salida, dir = 1, efecto, mix = 2, room = 2, damp = 2|
	senal = SinOsc.ar(880, 1)!4;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.3, 0.1, 0.3, -4, 0), gate, doneAction:2);
	//efecto = FreeVerb.ar(senal, mix, room, damp);
	//salida = senal+efecto;
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)


(
Tdef(\fin, {
	~grito = Synth(\grito);
	35.wait;
	~grito.set(\gate, 0);
	~sine = Synth(\sine);
	10.wait;
	~sine.free;
}));

Tdef(\fin).play;

(
Tdef(\miedo00, {
	1.wait;
	~bandpass5 = Synth(\bandpass5);
	0.25.wait;
	(
		d=OSCdef(\museOsck, {|msg|
			var delta1, delta2, delta3, delta4, delta5;
			msg.postln;
			delta1 = msg[1].linlin(-2000.0, 1996.1, 1, 10);
			delta2 = msg[1].linlin(-2000.0, 1996.1,4,20);
			delta3 = msg[1].linlin(-2000.0, 1996.1,10,20);
			delta4 = msg[1].linlin(-2000.0, 1996.1,100,300);
			delta5 = msg[1].linlin(-2000.0, 1996.1,5,20);
			~bandpass5.set(\freq1, delta1);
			~bandpass5.set(\freq2, delta2);
			~bandpass5.set(\range1, delta3);
			~bandpass5.set(\range2, delta4);
			~bandpass5.set(\frec, delta5);
		},'/muse/acc')
	);
	0.25.wait;
	5.do{
		var tiempo, time = ~wait;
		(
			r=OSCdef(\museOscr, {|msg|
				tiempo = msg[1].linlin(0.01, 0.99, 1, 20);
				msg[1].postln;
				~wait = tiempo;
			},'/muse/elements/theta_relative'
			);
		);
		3.wait;
		~escoje00 = Synth([\p00, \p01, \p02, \p03, \p04, \p04, \p05].choose);
		"1______________".postln;
		time.wait;
		~escoje01 = Synth([\bass, \bass0].choose);
		"2______________".postln;
		~escoje00 = Synth([\p00, \p01, \p02, \p03, \p04, \p04, \p05].choose);
		"3______________".postln;
		time.wait;
		~escoje01 = Synth([\bass, \bass0].choose);
		"4______________".postln;
		~escoje00 = Synth([\p00, \p01, \p02, \p03, \p04, \p04, \p05].choose);
		"5______________".postln;
		time.wait;
		~escoje01 = Synth([\bass, \bass0].choose);
		"6______________".postln;
		~escoje00 = Synth([\p00, \p01, \p02, \p03, \p04, \p04, \p05].choose);
		"7______________".postln;
		time.wait;
		~escoje01 = Synth([\bass, \bass0].choose);
		"8______________".postln;
	};
	1.wait;
	Tdef(\fin).play;
	d.free;
	4.wait;
	~bandpass5.free;
	1.do{
		var tiempo, time = ~wait;
		(
			r=OSCdef(\museOscr, {|msg|
				tiempo = msg[1].linlin(0.01, 0.99, 1, 20);
				msg[1].postln;
				~wait = tiempo;
			},'/muse/elements/theta_relative'
			);
		);
		3.wait;
		~escoje00 = Synth([\p00, \p01, \p02, \p03, \p04, \p04, \p05].choose);
		"1______________".postln;
		time.wait;
		~escoje01 = Synth([\bass, \bass0].choose);
		"2______________".postln;
		~escoje00 = Synth([\p00, \p01, \p02, \p03, \p04, \p04, \p05].choose);
		"3______________".postln;
		time.wait;
		~escoje01 = Synth([\bass, \bass0].choose);
		"4______________".postln;
		~escoje00 = Synth([\p00, \p01, \p02, \p03, \p04, \p04, \p05].choose);
		"5______________".postln;
		time.wait;
		~escoje01 = Synth([\bass, \bass0].choose);
	};
	r.free;

};
);
);


Tdef(\miedo00).play;



////////////


(
Tdef(\ritmos_clicks,
	{
		Synth(\ritmos1);
		Synth(\ritmos2);
	};
);
)

Tdef(\ritmos_clicks).play



(
SynthDef(\ritmos1, {| senal, paneo, out, freq = 1, env, gate = 1, salida|
	senal = LFNoise0.ar(freq);
	paneo = SinOsc.kr(0.5,0,2,0);
	env = EnvGen.ar(Env([0,0.2],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida,paneo,1));
}).add;
)

~ritmos1 = Synth(\ritmos1)


(
SynthDef(\ritmos2, {| senal, paneo, out, freq = 3, env, gate = 1, salida|
	senal = LFNoise0.ar(freq);
	paneo = SinOsc.kr(0.5,0,2,0);
	env = EnvGen.ar(Env([0,0.2],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(2, Pan2.ar(salida,paneo,1));
}).add;
)

~ritmos2 = Synth(\ritmos2)







////////////

/*
(
SynthDef(\bajobeat, {| senal, paneo, out, env, gate = 1, salida, dir = 0.3, efecto, mix = 2, room = 2, damp = 2|
	senal = PlayBuf.ar(~bajobeat_buf.numChannels, ~bajobeat_buf.bufnum, dir, loop:0, doneaction:0)*4;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.5, 1, 0.5, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~bajobeat = Synth(\bajobeat);
~bajobeat.set(\gate, 0);
~bajobeat.set(\dir, 2);
*/



////EJEMPLO DE CODIGO http://sccode.org/1-7

(
{ | dur = 0.15, atk = 0.005, amp = 1 |
	SinOsc.ar(
		EnvGen.ar( Env(
			NamedControl.kr(\freq_l, [2960, 70, 90]),
			NamedControl.kr(\freq_d, [0.07, 0.2]),
			NamedControl.kr(\freq_c, [-13, -1]),
		) ),
		mul:amp * EnvGen.ar(
			Env.perc( atk, dur - atk, curve: NamedControl.kr(\amp_c, [-1, 6])),
			doneAction: 2
		);
	) ! 2;
}.asSynthDef.name_("kick").add;

{ | atk = 0.01, dur = 0.15, freq = 50, amp=0.8 |
	BPF.ar(LFSaw.ar(freq), freq, 2, mul: EnvGen.kr( Env.perc( atk, dur-atk, amp, 6 ), doneAction: 2 )) ! 2;
}.asSynthDef.name_("bass").add;

{ | dur = 0.15, freq = 50, amp = 0.8, index = 10 |
	PMOsc.ar(freq, freq + 5, index, mul: amp * EnvGen.kr( Env.triangle( dur ), doneAction: 2 )) ! 2;
}.asSynthDef.name_("bazz").add;
)


(
Ppar([
	Pbind(*[
		instrument: \kick,
		delta: 1,
		dur: Pfunc({ thisThread.clock.beatDur }) / 4,
		amp: Pseq([
			Pseq([1], 16),
			Pseq([0.8, 1], 8),
			Pseq([1], 16),
			Pseq([0.8, 0.8, 0.9, 1], 8)
		], inf) * 0.8,
		freq_l: Pstutter(Prand(2.pow((1..4)),inf), Pseq([
			`[2960,70,90],
			`[1260,60,110],
			`[4360,60,120]
		],inf))
	]),
	Pbind(*[
		instrument: \bass,
		delta: 1/4,
		dur: Pkey(\delta) * Pfunc({ thisThread.clock.beatDur }),
		freq: Pseq([\r, 50,60,70], inf),
		amp:0.6
	]),
	Pbind(*[
		instrument: \bazz,
		delta: 1/4,
		dur: Pkey(\delta) * Pfunc({ thisThread.clock.beatDur }),
		freq: Pseq([\r, 30,35,40], inf),
		amp:0.2
	])
]).play(TempoClock(156/60), quant:[1])
)

// kick from above?
(
Pbind(*[
	instrument: \kick,
	delta: Pseq(Array.geom(540, 1, 1.015).reciprocal.reverse),
	dur: Pkey(\delta) * Pfunc({ thisThread.clock.beatDur }),
	atk: Pkey(\dur) / 6,
        amp: 0.8
]).play;
)



