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


///SOLEDAD 00


~lfn_4ch_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Soledad/Soledad00/LFN_4ch.wav");
~piercing_4ch_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Soledad/Soledad00/piercing_4ch.wav");
~you_mono_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Soledad/Soledad00/you.wav");
~are_mono_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Soledad/Soledad00/are.wav");
~not_mono_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Soledad/Soledad00/not.wav");
~alone_mono_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Soledad/Soledad00/alone.wav");





(
SynthDef(\lfn2, {| out = 0, gate = 1, amp = 0.7, dir = 0.4|
	var senal, env;
	senal = PlayBuf.ar(~lfn_4ch_buf.numChannels, ~lfn_4ch_buf.bufnum, dir,  loop:0, doneAction:0)*4;
	env = EnvGen.ar(Env.adsr(15, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)

~lfn2 = Synth(\lfn2);


(
SynthDef(\piercing, {| out = 0, gate = 1, amp = 0.7, dir = 0.2|
	var senal, env;
	senal = PlayBuf.ar(~piercing_4ch_buf.numChannels, ~piercing_4ch_buf.bufnum, dir,  loop:0, doneAction:0)*4;
	env = EnvGen.ar(Env.adsr(5, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)

~piercing = Synth(\piercing);
~piercing.set(\dir, 0.2);


(
SynthDef(\piercing1, {| out = 0, gate = 1, amp = 0.7, dir = 0.4|
	var senal, env;
	senal = PlayBuf.ar(~piercing_4ch_buf.numChannels, ~piercing_4ch_buf.bufnum, dir,  loop:0, doneAction:0)*4;
	env = EnvGen.ar(Env.adsr(15, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)

~piercing1 = Synth(\piercing1);
~piercing1.set(\dir, 0.5);



(
SynthDef(\piercing2, {| out = 0, gate = 1, amp = 0.7, dir = 0.5|
	var senal, env;
	senal = PlayBuf.ar(~piercing_4ch_buf.numChannels, ~piercing_4ch_buf.bufnum, dir,  loop:0, doneAction:0)*4;
	env = EnvGen.ar(Env.adsr(15, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)

~piercing2 = Synth(\piercing2);
~piercing2.set(\dir, 0.5);


(
SynthDef(\you, {| out = 0, gate = 1, amp = 0.7, dir = 0.9|
	var senal, env;
	senal = PlayBuf.ar(~you_mono_buf.numChannels, ~you_mono_buf.bufnum, dir,  loop:0, doneAction:0)*8;
	env = EnvGen.ar(Env.adsr(15, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	//senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)

~you = Synth(\you);


(
SynthDef(\are, {| out = 1, gate = 1, amp = 0.7, dir = 0.9|
	var senal, env;
	senal = PlayBuf.ar(~are_mono_buf.numChannels, ~are_mono_buf.bufnum, dir,  loop:0, doneAction:0)*14;
	env = EnvGen.ar(Env.adsr(15, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	//senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)

~are = Synth(\are);


(
SynthDef(\not, {| out = 2, gate = 1, amp = 0.7, dir = 1|
	var senal, env;
	senal = PlayBuf.ar(~not_mono_buf.numChannels, ~not_mono_buf.bufnum, dir,  loop:0, doneAction:0)*14;
	env = EnvGen.ar(Env.adsr(15, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	//senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)

~not = Synth(\not);


(
SynthDef(\alone, {| out = 3, gate = 1, amp = 0.7, dir = 0.85|
	var senal, env;
	senal = PlayBuf.ar(~alone_mono_buf.numChannels, ~alone_mono_buf.bufnum, dir,  loop:0, doneAction:0)*14;
	env = EnvGen.ar(Env.adsr(15, 3, 0.7, 1, 1, -4, 0), gate, dir, doneAction:2);
	senal = senal*env;
	//senal = Pan2.ar(senal, 0, amp);
	Out.ar(out, senal);
}).add
)

~alone = Synth(\alone);


(
Tdef(\youarenot,
	{
		~you = Synth(\you);
		1.wait;
		~are = Synth(\are);
		0.8.wait;
		~not = Synth(\not);
		1.wait;
		~alone = Synth(\alone);
	};
);
);

Tdef(\youarenot).play;



(
Tdef(\youare,
	{
		~you = Synth(\you);
		1.wait;
		~are = Synth(\are);
		1.wait;
		~alone = Synth(\alone);
	};
);
);

Tdef(\youare).play;




(
Tdef(\areNot, {
	1.wait;
	~piercing1 = Synth(\piercing1);
	1.wait;
	~piercing = Synth(\piercing);
	2.wait;
	~lfn2 = Synth(\lfn2);
	10.wait;
	7.do{
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
		~escoje = Synth([\you, \are, \not, \alone].choose);
		"1______________".postln;
		time.wait;
		~escoje = Synth([\you, \are, \not, \alone].choose);
		"2______________".postln;
		time.wait;
		~escoje = Synth([\you, \are, \not, \alone].choose);
		"3______________".postln;
		time.wait;
		~escoje = Synth([\you, \are, \not, \alone].choose);
		"4______________".postln;
		time.wait;
	};
	r.free;
	};
);
)

Tdef(\areNot).play;



(
x=OSCdef(\museOscx, {|msg|
	var dir;
	msg[1].postln;
	if(msg[1]==1,
		{"blink".post;

			~piercing2.set(\dir, [0.5, 0.6, 0.7, 0.8, 0.9, 1].choose);
		}
	);
},
'/muse/elements/blink'
);
)

~piercing2 = Synth(\piercing2)

x.free



