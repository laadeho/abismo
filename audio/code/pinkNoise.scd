

(
SynthDef(\pinkNoise, {| senal, paneo, out, xpos = 1, ypos = 1, env, gate = 1, salida, amp = 1|
	senal = Pan4.ar(in: PinkNoise.ar, xpos: SinOsc.kr(xpos), ypos: SinOsc.kr(ypos), level: 0.1);
	env = EnvGen.ar(Env([0,amp],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(1), gate, doneAction:2);
	Out.ar(0,senal);
}).add;
)

~pinkNoise = Synth(\pinkNoise)
~pinkNoise.set(\gate, 0)



(
e=OSCdef(\museOsca, {|msg|
	var delta1, delta2;
	msg.postln;
	delta1 = msg[1].linlin(0.1,0.9,1,10);
	delta2 = msg[1].linlin(0.1,0.9,11,20);
	~pinkNoise.set(\xpos, delta1);
	~pinkNoise.set(\ypos, delta2);
},'/muse/elements/alpha_relative')
)