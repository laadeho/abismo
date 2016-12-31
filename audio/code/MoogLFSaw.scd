

(
SynthDef(\prueba, {| senal, freq = 20 paneo, out, env, gate = 1, salida, oscilador = 0.5|
	senal = BMoog.ar(LFSaw.ar([freq * 0.99, freq * 1.01], 0.5, 0.1), SinOsc.kr(SinOsc.kr(oscilador),1.5pi,1550,1800), 0.2, 2);
	env = EnvGen.ar(Env([0,1],[5]));
	paneo = SinOsc.kr(0.1,0,2,0);
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(10), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)


~moog = Synth(\prueba)
~moog.set(\gate, 0)
~moog.set(\freq, 150)
~moog.set(\oscilador, 0.5)


(
j=OSCdef(\museOsca, {|msg|
	var delta1, delta2;
	msg.postln;
	delta1 = msg[1].linlin(0.1,0.9,20,60);
	delta2 = msg[1].linlin(0.1,0.9,0.05,5);
	~moog.set(\freq, delta1);
	~moog.set(\oscilador, delta2);
},'/muse/elements/alpha_relative')
)
