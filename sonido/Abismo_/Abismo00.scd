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



/////////////////// ABISMO00

pulso srg osc otros


(
SynthDef(\canto, {| senal, paneo, frec1 = 82, frec2 = 164, out, env, gate = 1, salida, efecto, dir = 0.85, mix = 2, room = 6, damp = 6, salida1, salida2, bus = 0|
	senal = PlayBuf.ar(~cantost_buf.numChannels, ~cantost_buf.bufnum, dir, loop:0, doneaction:0)*2;
	efecto = FreeVerb.ar(senal, mix, room, damp);
	env = EnvGen.ar(Env.adsr(1, 3, 0.4, 1, 0.5, -4, 0), gate, doneAction:2);
	salida1 = senal+efecto;
	salida2 = salida1*env;
	Out.ar(bus, Pan4.ar(salida2,paneo,1));
}).add;
)

~canto = Synth(\canto)
~canto.set(\mix, 2);
~canto.set(\room, 6);
~canto.set(\damp, 6);
~canto.set(\gate, 0);



(
		y=OSCdef(\museOscy, {|msg|
			var freq;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~canto.set(\bus, [0, 1, 2, 3].choose);
				}
			)
		},
		'/muse/elements/blink'
		);
	)


(
SynthDef(\blip, {| senal, paneo, frec1 = 110, frec2 = 110, out, env, gate = 1, armonicos = 1, salida|
	senal = Blip.ar(203,armonicos, 2);
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env.adsr(0.1, 0.5, 0.1, 0.1, 0.5, -4, 0), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo));
}).add;
)

~blip = Synth(\blip)
~blip.set(\gate, 0)
~blip.set(\armonicos,5);



(
i=OSCdef(\museOscb, {|msg|
	var alpha1, alpha2, alpha3;
	msg.postln;
	alpha1 = msg[1].linlin(0.1,0.9,0,40);
	~blip.set(\armonicos, alpha1);
},'/muse/elements/alpha_relative')
)

i.free;

Tdef(\abismo00).play

(
Tdef(\abismo00, {
	1.wait;
	~canto = Synth(\canto);
	1.wait;
	(
		y=OSCdef(\museOscy, {|msg|
			var freq;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~canto.set(\bus, [0, 1, 2, 3].choose);
				}
			)
		},
		'/muse/elements/blink'
		);
	);
	2.wait;
	~blip = Synth(\blip);
	(
		i=OSCdef(\museOscb, {|msg|
			var alpha1, alpha2, alpha3;
			msg.postln;
			alpha1 = msg[1].linlin(0.1,0.9,0,40);
			~blip.set(\armonicos, alpha1);
		},'/muse/elements/alpha_relative')
	);
});
)