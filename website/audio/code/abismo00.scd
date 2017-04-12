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

///ABISMO 00


~abismo00_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/abismo00.wav");
~abismo00Mono_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/abismo00Mono.wav");

(
SynthDef(\abismo00, {| senal, paneo, out, env, gate = 1, salida|
	senal = PlayBuf.ar(~abismo00_buf.numChannels, ~abismo00_buf.bufnum, 1, loop:0, doneaction:0)*3;
	env = EnvGen.ar(Env.adsr(10, 3, 0.5, 20, 0.6, -4, 0), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)


~abismo00 = Synth(\abismo00);

(
SynthDef(\bajoabismo00, {|senal, paneo, out, env, gate = 1, salida, armonicos = 7|
	senal = Blip.ar(82,armonicos);
	env = EnvGen.ar(Env.adsr(600, 0.4, 0.4, 15, 0.3, -4, 0), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida, paneo, 1));
}).add;
);

~bajoabismo00 = Synth(\bajoabismo00);
~bajoabismo00.set(\gate, 0);


(
			i=OSCdef(\museOsci, {|msg|
				var alpha1, alpha2, alpha3;
				msg.postln;
				alpha1 = msg[1].linlin(0.1,0.9,0,7);
				~bajoabismo00.set(\armonicos, alpha1);
			},'/muse/elements/alpha_relative')
		);

i.free;


(
SynthDef(\abismoMuse00, {| senal, paneo, out, env, gate = 1, salida, efecto, senal1, grains, trate, dur, rate, kr1 = 2, kr2 = 0.1 |
	trate = kr1;
    dur = 4 / trate;
    rate = kr2; //Dseq([10, 1, 1, 0.5, 0.5, 0.2, 0.1], inf);
    grains = TGrains.ar(2, Impulse.ar(trate), ~abismo00Mono_buf, rate, 120, dur, Dseq([-1, 1], inf), 0.1, 2)*4;
	env = EnvGen.ar(Env.adsr(1, 3, 0.5, 15, 0.6, -4, 0), gate, doneAction:2);
	salida = env*grains;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)


~abismoMuse00 = Synth(\abismoMuse00);
~abismoMuse00.set(\kr1, 0.3);
~abismoMuse00.set(\kr2, 1);
~abismoMuse00.set(\gate, 0);


(
b=OSCdef(\museOscb, {|msg|
	var alpha1, alpha2;
	msg.postln;
	alpha1 = msg[1].linlin(0.1,0.9,0.3,4);
	alpha2 = msg[1].linlin(0.1,0.9,0.1,10);
	~abismoMuse00.set(\kr1, alpha1);
	~abismoMuse00.set(\kr2, alpha2);
},'/muse/elements/theta_relative')
)

b.free;


s.boot;
b = Buffer.read(s, Platform.resourceDir +/+ "sounds/a11wlk01.wav");
b.play

(
{
    var trate, dur, rate;
    trate = MouseY.kr(2,200,1);
    dur = 4 / trate;
    rate = Dseq([10, 1, 1, 0.5, 0.5, 0.2, 0.1], inf);
    TGrains.ar(2, Impulse.ar(trate), ~abismo00Mono_buf, rate, MouseX.kr(0,BufDur.kr(b)), dur, Dseq([-1, 1], inf), 0.1, 2);
}.scope(zoom: 4);
)


(
Tdef(\abismo00, {
	1.wait;
	~abismoMuse00 = Synth(\abismoMuse00);
	~bajoabismo00 = Synth(\bajoabismo00);
	20.wait;
	(
		b=OSCdef(\museOscb, {|msg|
			var alpha1, alpha2;
			msg.postln;
			alpha1 = msg[1].linlin(0.1,0.9,0.3,4);
			alpha2 = msg[1].linlin(0.1,0.9,0.1,10);
			~abismoMuse00.set(\kr1, alpha1);
			~abismoMuse00.set(\kr2, alpha2);
		},'/muse/elements/theta_relative')
	);
	15.wait;
	(
		i=OSCdef(\museOsci, {|msg|
			var alpha1, alpha2, alpha3;
			msg.postln;
			alpha1 = msg[1].linlin(0.1,0.9,0,7);
			~bajoabismo00.set(\armonicos, alpha1);
		},'/muse/elements/alpha_relative')
	);
	10.wait;
	b.free;
	10.wait;
	(
		b=OSCdef(\museOscb, {|msg|
			var alpha1, alpha2;
			msg.postln;
			alpha1 = msg[1].linlin(0.1,0.9,0.3,4);
			alpha2 = msg[1].linlin(0.1,0.9,0.1,10);
			~abismoMuse00.set(\kr1, alpha1);
			~abismoMuse00.set(\kr2, alpha2);
		},'/muse/elements/theta_relative')
	);
	10.wait;
	b.free;
	10.wait;
	(
		b=OSCdef(\museOscb, {|msg|
			var alpha1, alpha2;
			msg.postln;
			alpha1 = msg[1].linlin(0.1,0.9,0.3,4);
			alpha2 = msg[1].linlin(0.1,0.9,0.1,10);
			~abismoMuse00.set(\kr1, alpha1);
			~abismoMuse00.set(\kr2, alpha2);
		},'/muse/elements/theta_relative')
	);
	50.wait;
	~abismo00 = Synth(\abismo00);
	120.wait;
	~abismoMuse00.set(\gate, 0);
	~bajoabismo00.set(\gate, 0);
	10.wait;
	b.free;
	1.wait;
	i.free;
	110.wait;
	~abismo00.set(\gate, 0);
};
);
);

Tdef(\abismo00).play;


