s.options.device_("ASIO : ASIO4ALL v2");
s.boot;
s.meter;
Server.default.makeGui;
s.recChannels_(4); // or whatever number of channels
s.record;
stop.record;

s.options.memSize = 65536;  // e.g., could be different for you
myServer.boot;

c = 4;
s.options.numOutputBusChannels = c;
s.options.sampleRate = 48000;
s.boot;
s.recChannels = c;
s.recHeaderFormat = "WAV";


//// TRANQUILIDAD00


~tranquil00_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Tranquilidad/tranquil00.wav");
~night_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Tranquilidad/Night_mono.wav");
~tranquilBajo_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Tranquilidad/tranquilBajo_4chan.wav");
~bell00_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Tranquilidad/Bell00.wav");
~bell01_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Tranquilidad/Bell01.wav");
~bell02_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Tranquilidad/Bell02.wav");
~bell03_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Tranquilidad/Bell03.wav");


(
SynthDef(\tranquil00, {| senal, paneo, out, env, gate = 1, salida, dir = 0.9, efecto, mix = 2, room = 2, damp = 2|
	senal = PlayBuf.ar(~tranquil00_buf.numChannels, ~tranquil00_buf.bufnum, dir, loop:0, doneaction:0)*3;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.5, 15, 0.5, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~tranquil00 = Synth(\tranquil00);



(
SynthDef(\tranquilBajo, {| senal, paneo, out, env, gate = 1, salida, dir = 1, efecto, mix = 2, room = 2, damp = 2|
	senal = PlayBuf.ar(~tranquilBajo_buf.numChannels, ~tranquilBajo_buf.bufnum, dir, loop:0, doneaction:0);
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.5, 15, 0.5, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~tranquilBajo = Synth(\tranquilBajo);


(
SynthDef(\night00, {| senal, paneo, out, env, gate = 1, salida, efecto, senal1, grains, trate, dur, rate, kr1 = 2, kr2 = 0.1 |
	trate = kr1;
    dur = 4 / trate;
    rate = kr2; //Dseq([10, 1, 1, 0.5, 0.5, 0.2, 0.1], inf);
    grains = TGrains.ar(2, Impulse.ar(trate), ~night_buf, rate, 120, dur, Dseq([-1, 1], inf), 0.1, 2)*4;
	env = EnvGen.ar(Env.adsr(1, 3, 0.5, 15, 0.6, -4, 0), gate, doneAction:2);
	salida = env*grains;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~night00 = Synth(\night00);


(
SynthDef(\night01, {| senal, paneo, out, env, gate = 1, salida, efecto, senal1, grains, trate, dur, rate, kr1 = 2, kr2 = 0.1 |
	trate = kr1;
    dur = 4 / trate;
    rate = kr2; //Dseq([10, 1, 1, 0.5, 0.5, 0.2, 0.1], inf);
    grains = TGrains.ar(2, Impulse.ar(trate), ~night_buf, rate, 120, dur, Dseq([-1, 1], inf), 0.1, 2)*4;
	env = EnvGen.ar(Env.adsr(1, 3, 0.5, 15, 0.6, -4, 0), gate, doneAction:2);
	salida = env*grains;
	Out.ar(2, Pan4.ar(salida,paneo,1));
}).add;
)

~night01 = Synth(\night01);



(
SynthDef(\bell00, {| senal, paneo, out, env, gate = 1, salida, dir = 0.4, efecto, mix = 0.5, room = 1, damp = 2|
	senal = PlayBuf.ar(~bell00_buf.numChannels, ~bell00_buf.bufnum, dir, loop:0, doneaction:0)*3;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.6, 1, 1, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	salida = salida+efecto;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~bell00 = Synth(\bell00);


(
SynthDef(\bell01, {| senal, paneo, out, env, gate = 1, salida, dir = 0.4, efecto, mix = 0.5, room = 1, damp = 2|
	senal = PlayBuf.ar(~bell01_buf.numChannels, ~bell01_buf.bufnum, dir, loop:0, doneaction:0)*1;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.6, 1, 1, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	salida = salida+efecto;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~bell01 = Synth(\bell01);



(
SynthDef(\bell02, {| senal, paneo, out, env, gate = 1, salida, dir = 0.5, efecto, mix = 0.5, room = 1, damp = 2|
	senal = PlayBuf.ar(~bell02_buf.numChannels, ~bell02_buf.bufnum, dir, loop:0, doneaction:0)*1;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.6, 1, 1, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	salida = salida+efecto;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~bell02 = Synth(\bell02);


(
SynthDef(\bell03, {| senal, paneo, out, env, gate = 1, salida, dir = 0.3, efecto, mix = 0.5, room = 1, damp = 2|
	senal = PlayBuf.ar(~bell03_buf.numChannels, ~bell03_buf.bufnum, dir, loop:0, doneaction:0)*2;
	env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.6, 1, 1, -4, 0), gate, doneAction:2);
	efecto = FreeVerb.ar(senal, mix, room, damp);
	salida = senal*env;
	salida = salida+efecto;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~bell03 = Synth(\bell03);


(
x=OSCdef(\museOscx, {|msg|
	var freq;
	msg[1].postln;
	if(msg[1]==1,
		{"blink".post;
			~choose = Synth([\bell02, \bell00, \bell01, \bell03].choose);
		},{
			"NOT".postln;
		}
	)
},
'/muse/elements/blink'
);
)






(
Tdef(\Tranquil00, {
	1.wait;
	~night01 = Synth(\night01);
	1.wait;
	~night00 = Synth(\night00);
	5.wait;
	(
		b=OSCdef(\museOscb, {|msg|
			var alpha1, alpha2, alpha3, alpha4;
			msg.postln;
			alpha1 = msg[1].linlin(0.1,0.9,0.3,4);
			alpha2 = msg[1].linlin(0.1,0.9,0.1,10);
			alpha3 = msg[1].linlin(0.1,0.9,0.1,6);
			alpha4 = msg[1].linlin(0.1,0.9,0.5,15);
			~night00.set(\kr1, alpha1);
			~night00.set(\kr2, alpha2);
			~night01.set(\kr1, alpha3);
			~night01.set(\kr2, alpha4);
		},'/muse/elements/alpha_relative')
	);
	20.wait;
	~tranquil00 = Synth(\tranquil00);
	15.wait;
	~tranquilBajo = Synth(\tranquilBajo);
	(
		k=OSCdef(\museOsck, {|msg|
			var acc1;
			msg.postln;
			acc1 = msg[1].linlin(-2000.0, 1996.1, 0.3, 1.2);
			~tranquilBajo.set(\dir, acc1);
		},'/muse/acc')
	);
	10.wait;
	(
		x=OSCdef(\museOscx, {|msg|
			var freq;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~choose = Synth([\bell02, \bell00, \bell01, \bell03].choose);
				},{
					"NOT".postln;
				}
			)
		},
		'/muse/elements/blink'
		);
	);
	20.wait;
	~tranquilBajo.set(\gate, 0);
	5.wait;
	~tranquil00.set(\gate, 0);
	5.wait;
	~night00.set(\gate, 0);
	2.wait;
	~night01.set(\gate, 0);
	x.free;
	0.25.wait;
	k.free;
	0.25.wait;
	b.free;
};
);
);

Tdef(\Tranquil00).play;


