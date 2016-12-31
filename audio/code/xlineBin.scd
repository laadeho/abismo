


(
SynthDef(\binaural1_asc, {| senal, paneo, out, freq1 = 80, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(30,80,150),0,1)/2;
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[50]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

a = Synth(\binaural1_asc)
a.set(\gate, 0)

(
SynthDef(\binaural1_desc, {| senal, paneo, out, freq1 = 80, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(80,30,70),0,1)/2;
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

c = Synth(\binaural1_desc)
c.set(\gate, 0)

(
SynthDef(\binaural2_asc, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(30.5,80.5,150),0,1)/2;
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[50]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

b = Synth(\binaural2_asc)
b.set(\gate, 0)


(
SynthDef(\binaural2_desc, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(80.5,30.5,70),0,1)/2;
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

d = Synth(\binaural2_desc)
d.set(\gate, 0)


(
Tdef(\binaurales,
	{
		a = Synth(\binaural1_asc);
		b = Synth(\binaural2_asc);
		c = Synth(\binaural1_desc);
		d = Synth(\binaural2_desc);
	};
);
)

Tdef(\binaurales).play