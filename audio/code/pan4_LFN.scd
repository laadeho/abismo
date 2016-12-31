


(
SynthDef(\pan4_LFN, {| senal, paneo, out, freq1 = 600, freq2 = 13000 env, gate = 1, salida|
	senal = SinOsc.ar(freq: LFNoise0.kr(800).range(freq1, freq2), mul: 0.1);
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(5), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~pan4_LFN = Synth(\pan4_LFN)
~pan4_LFN.set(\gate, 0)

~pan4_LFN.set(\freq1, 60)
~pan4_LFN.set(\freq2, 100)

(
e=OSCdef(\museOsca, {|msg|
	var delta1, delta2;
	msg.postln;
	delta1 = msg[1].linlin(0.1,0.9,60,600);
	delta2 = msg[1].linlin(0.1,0.9,100,13000);
	~pan4_LFN.set(\freq1, delta1);
	~pan4_LFN.set(\freq2, delta2);
},'/muse/elements/alpha_relative')
)


(
x=OSCdef(\museOscx, {|msg|
	msg[1].postln;
	if(msg[1]==1,
		{"blink".post;
			~pan4_LFN.set(\freq1, [60, 13000, 600, 10000, 1000 ].choose);
			~pan4_LFN.set(\freq2, [60, 13000, 600, 10000, 1000 ].choose);
		}
	);
	},
	'/muse/elements/blink'
);
)