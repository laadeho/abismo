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

///EXPECTATIVA 01



~ah00_4ch_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Expectativa/Expectativa01/ah00_4ch.wav");
~ah01_4ch_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Expectativa/Expectativa01/ah01_4ch.wav");
~ah02_4ch_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Expectativa/Expectativa01/ah02_4ch.wav");
~ah03_4ch_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Expectativa/Expectativa01/ah03_4ch.wav");
~ah04_4ch_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Expectativa/Expectativa01/ah04_4ch.wav");
~ah05_4ch_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Expectativa/Expectativa01/ah05_4ch.wav");
~mn_4ch_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Expectativa/Expectativa01/mn_4ch.wav");

(
SynthDef(\ah00, {| out = 0, gate = 1, amp = 0.7, dir = 0.4|
	var senal, env;
	senal = PlayBuf.ar(~ah00_4ch_buf.numChannels, ~ah00_4ch_buf.bufnum, dir,  loop:0, doneAction:0)*3;
	env = EnvGen.ar(Env.adsr(5, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)


~ah00 = Synth(\ah00);
~s00.set(\gate,0);


(
SynthDef(\ah01, {| out = 0, gate = 1, amp = 0.7, dir = 0.4|
	var senal, env;
	senal = PlayBuf.ar(~ah01_4ch_buf.numChannels, ~ah01_4ch_buf.bufnum, dir,  loop:0, doneAction:0)*3;
	env = EnvGen.ar(Env.adsr(5, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)


~ah01 = Synth(\ah01);
~ah01.set(\gate,0);


(
SynthDef(\ah02, {| out = 0, gate = 1, amp = 0.7, dir = 0.4|
	var senal, env;
	senal = PlayBuf.ar(~ah02_4ch_buf.numChannels, ~ah02_4ch_buf.bufnum, dir,  loop:0, doneAction:0)*3;
	env = EnvGen.ar(Env.adsr(5, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)


~ah02 = Synth(\ah02);
~ah02.set(\gate,0);


(
SynthDef(\ah03, {| out = 0, gate = 1, amp = 0.7, dir = 0.4|
	var senal, env;
	senal = PlayBuf.ar(~ah03_4ch_buf.numChannels, ~ah03_4ch_buf.bufnum, dir,  loop:0, doneAction:0)*3;
	env = EnvGen.ar(Env.adsr(5, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)


~ah03 = Synth(\ah03);
~ah03.set(\gate,0);


(
SynthDef(\ah04, {| out = 0, gate = 1, amp = 0.7, dir = 0.4|
	var senal, env;
	senal = PlayBuf.ar(~ah04_4ch_buf.numChannels, ~ah04_4ch_buf.bufnum, dir,  loop:0, doneAction:0)*3;
	env = EnvGen.ar(Env.adsr(5, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)


~ah04 = Synth(\ah04);
~ah04.set(\gate,0);

(
SynthDef(\ah05, {| out = 0, gate = 1, amp = 0.7, dir = 0.4|
	var senal, env;
	senal = PlayBuf.ar(~ah05_4ch_buf.numChannels, ~ah05_4ch_buf.bufnum, dir,  loop:0, doneAction:0)*3;
	env = EnvGen.ar(Env.adsr(5, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)


~ah05 = Synth(\ah05);
~ah05.set(\gate,0);


(
SynthDef(\mn, {| out = 0, gate = 1, amp = 0.7, dir = 0.6|
	var senal, env;
	senal = PlayBuf.ar(~mn_4ch_buf.numChannels, ~mn_4ch_buf.bufnum, dir,  loop:0, doneAction:0)*2;
	env = EnvGen.ar(Env.adsr(5, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)


~mn = Synth(\mn);
~mn.set(\gate,0);




(
Tdef(\ah, {
	1.wait;
		~mn = Synth(\mn);
	10.wait;
	5.do{
		var tiempo, time = ~wait;
		(
			r=OSCdef(\museOscr, {|msg|
				tiempo = msg[1].linlin(0.01, 0.99, 1, 20);
				msg[1].postln;
				~wait = tiempo;
				},'/muse/elements/theta_relative'
			);
		);
		1.wait;
		~escoje = Synth([\ah00, \ah01, \ah02, \ah03, \ah04, \ah04, \ah05].choose);
		"1______________".postln;
		time.wait;
		~escoje = Synth([\ah00, \ah01, \ah02, \ah03, \ah04, \ah04, \ah05].choose);
		"2______________".postln;
		time.wait;
		~escoje = Synth([\ah00, \ah01, \ah02, \ah03, \ah04, \ah04, \ah05].choose);
		"3______________".postln;
		time.wait;
		~escoje = Synth([\ah00, \ah01, \ah02, \ah03, \ah04, \ah04, \ah05].choose);
		"4______________".postln;
		time.wait;
		~escoje = Synth([\ah00, \ah01, \ah02, \ah03, \ah04, \ah04, \ah05].choose);
		"5______________".postln;
		time.wait;
		~escoje = Synth([\ah00, \ah01, \ah02, \ah03, \ah04, \ah04, \ah05].choose);
		"6______________".postln;
		time.wait;
		~escoje = Synth([\ah00, \ah01, \ah02, \ah03, \ah04, \ah04, \ah05].choose);
		"7______________".postln;
		time.wait;
		~escoje = Synth([\ah00, \ah01, \ah02, \ah03, \ah04, \ah04, \ah05].choose);
		"8______________".postln;
	};
	r.free;
	};
);
)

Tdef(\ah).play;





