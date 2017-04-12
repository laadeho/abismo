

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
j=OSCdef(\museOsca, {|msg|
	var delta1, delta2;
	msg.postln;
	delta1 = msg[1].linlin(0.1,0.9,1,20);
	delta2 = msg[1].linlin(0.1,0.9,3,40);
	~ritmos1.set(\freq, delta1);
	~ritmos2.set(\freq, delta2);
},'/muse/elements/alpha_relative')
)


(
SynthDef(\ritmos1, {| senal, paneo, out, freq = 1, env, gate = 1, salida|
	senal = LFNoise0.ar(freq);
	paneo = SinOsc.kr(0.5,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
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
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida,paneo,1));
}).add;
)

~ritmos2 = Synth(\ritmos2)