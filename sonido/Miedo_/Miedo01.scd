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


///////// MIEDO 01 /////////////////


~cellosolo_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Hemisferio/AudiosHemisferio/cello_solo1.wav");
1.5.wait;
~cellosoloMONO_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Hemisferio/AudiosHemisferio/cello_soloMONO.wav");
1.5.wait;
~miedo01_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Miedo/miedo01_4ch.wav");

~monks_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Miedo/monks_4ch.wav");

(
		SynthDef(\celloarm00, {| senal, paneo, out, env, gate = 1, salida, efecto, senal1, grains, trate, dur, rate, kr1 = 2, kr2 = 0.1 |
			trate = kr1;
			dur = 4 / trate;
			rate = kr2; //Dseq([10, 1, 1, 0.5, 0.5, 0.2, 0.1], inf);
			grains = TGrains.ar(2, Impulse.ar(trate), ~cellosoloMONO_buf, rate, 120, dur, Dseq([-1, 1], inf), 0.1, 2)*3;
			env = EnvGen.ar(Env.adsr(1, 3, 0.5, 15, 0.6, -4, 0), gate, doneAction:2);
			salida = env*grains;
			Out.ar(0, salida);
		}).add;
	);
	1.wait;
	~celloarm00 = Synth(\celloarm00);
	"sinte celloarm00 OK".postln;
	1.5.wait;
	~celloarm00.set(\gate, 0);
	1.wait;
	(
		SynthDef(\celloarm01, {| senal, paneo, out, env, gate = 1, salida, efecto, senal1, grains, trate, dur, rate, kr1 = 2, kr2 = 0.1 |
			trate = kr1;
			dur = 4 / trate;
			rate = kr2; //Dseq([10, 1, 1, 0.5, 0.5, 0.2, 0.1], inf);
			grains = TGrains.ar(2, Impulse.ar(trate), ~cellosoloMONO_buf, rate, 120, dur, Dseq([-1, 1], inf), 0.1, 2)*3;
			env = EnvGen.ar(Env.adsr(1, 3, 0.5, 15, 0.6, -4, 0), gate, doneAction:2);
			salida = env*grains;
			Out.ar(2, salida);
		}).add;
	);////// ESTE SINTE SALE POR BUS 2 !!!!
	1.wait;
	~celloarm01 = Synth(\celloarm01);
	"sinte celloarm01 OK".postln;
	1.5.wait;
	~celloarm01.set(\gate, 0);
	1.wait;

(
		SynthDef(\miedo01, {| senal, paneo, out, env, gate = 1, salida, dir = 0.5|
			senal = PlayBuf.ar(~miedo01_buf.numChannels, ~miedo01_buf.bufnum, dir, loop:0, doneaction:0)*6;
			env = EnvGen.ar(Env.adsr(1, 3, 0.4, 20, 0.4, -4, 0), gate, doneAction:2);
			salida = senal*env;
			Out.ar(0, Pan4.ar(salida,paneo,1));
		}).add;
	);

~miedo01 = Synth(\miedo01)

(
		SynthDef(\monks, {| senal, paneo, out, env, gate = 1, salida, dir = 0.7|
			senal = PlayBuf.ar(~monks_buf.numChannels, ~monks_buf.bufnum, dir, loop:0, doneaction:0);
			env = EnvGen.ar(Env.adsr(1, 3, 0.4, 20, 0.4, -4, 0), gate, doneAction:2);
			salida = senal*env;
			Out.ar(0, Pan4.ar(salida,paneo,1));
		}).add;
	);

~monks = Synth(\monks)

(
Tdef(\Miedo01, {
	~monks = Synth(\monks);
	10.wait;
	~celloarm00 = Synth(\celloarm00);
	2.wait;
	~celloarm01 = Synth(\celloarm01);
	5.wait;
	~miedo01 = Synth(\miedo01);
	10.do{
		(
			b=OSCdef(\museOscb, {|msg|
				var beta1;
				msg.postln;
				beta1 = msg[1].linlin(0.1,0.9,0.1,10);
				~celloarm00.set(\kr1, beta1);
			},'/muse/elements/beta_relative')
		);
		1.wait;
		(
			c=OSCdef(\museOscc, {|msg|
				var beta1;
				msg.postln;
				beta1 = msg[1].linlin(0.1,0.9,0.1,10);
				~celloarm01.set(\kr2, beta1);
			},'/muse/elements/beta_relative')
		);
		~monks.set(\gate, 0);
		3.wait;
		c.free;
		3.wait;
		b.free;
	};
	~celloarm00.set(\gate, 0);
	~celloarm01.set(\gate, 0);
	~miedo01.set(\gate, 0);
});
)

Tdef(\Miedo01).play;