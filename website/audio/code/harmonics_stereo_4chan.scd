



(
SynthDef(\harmonics_stereo, {| snd, pan, rq = 0.01, fundamental = 50, frec = 32, env, gate = 1, salida|
	var harm = [1, 2, 3, 4, 5, 6, 7, 8], harm1 = [1, 2, 3, 4, 5, 6, 7],  harm2 = [1, 2, 3, 4, 5, 6],  harm3 = [1, 2, 3, 4, 5];
	snd = BPF.ar(in: Saw.ar(frec, LFPulse.ar(harm, width: 0.1)), freq: harm * fundamental, rq: rq, mul: 20);
	snd = Splay.ar(snd);
	//env = EnvGen.ar(Env([0,1],[5]));
	//salida = bpf*env;
	//salida = bpf*EnvGen.ar(Env.cutoff(1), gate, doneAction:2);
	pan = Pan4.ar(in: snd);
	Out.ar(0, pan);
}).add;
)

~harmonics_stereo = Synth(\harmonics_stereo)


(
j=OSCdef(\museOsca, {|msg|
	var delta1, delta2, delta3, delta4, delta5;
	msg.postln;
	delta1 = msg[1].linlin(0.1,0.9,40,2200);
	delta2 = msg[1].linlin(0.1,0.9,0.01,0.05);
	delta3 = msg[1].linlin(0.1,0.9,1,50);
	delta4 = msg[1].linlin(0.1,0.9,10,10);
	delta5 = msg[1].linlin(0.1,0.9,300,13000);
	~harmonics_stereo.set(\fundamental, delta1);
	~harmonics_stereo.set(\rq, delta2);
},'/muse/elements/alpha_relative')
)

(
x=OSCdef(\museOscx, {|msg|
	var harm, frec;
	msg[1].postln;
	if(msg[1]==1,
		{"blink".post;
			~harmonics_stereo.set(\frec, [3, 13, 32, 300, 3000].choose);
		}
	);
	},
	'/muse/elements/blink'
);
)


(
SynthDef(\harmonics_4chan, {| snd, pan, out, xpos = 1, ypos = 1, fundamental = 110, frec = 300, freq1 = 4, freq2 = 8, range1 = 1, range2 = 10 env, gate = 1, salida, bpf|
	var harm = [1, 2, 3, 4];
	snd = BPF.ar(in: Saw.ar(32, LFPulse.ar(harm, width: 0.01)), freq: harm * fundamental, rq: 0.01, mul: 20);
	//snd = Splay.ar(snd, );
	//env = EnvGen.ar(Env([0,1],[5]));
	//salida = bpf*env;
	//salida = bpf*EnvGen.ar(Env.cutoff(1), gate, doneAction:2);
	pan = Pan4.ar(in: snd);
	Out.ar(0, pan);
}).add;
)

~harmonics_4chan = Synth(\harmonics_4chan)