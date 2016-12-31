


(
SynthDef(\bandpass, {| saw, pan, out, xpos = 1, ypos = 1, frec = 300, freq1 = 4, freq2 = 8, range1 = 1, range2 = 10 env, gate = 1, salida, bpf|
	var lfn1 = LFNoise2.kr(freq1), lfn2 = LFNoise2.kr(freq2);
	saw = Saw.ar( frec, mul: LFPulse.kr(freq: LFNoise1.kr(freq1).range(range1, range2), width: 0.1));
	bpf = BPF.ar(in: saw, freq: lfn1.range(500, 2500), rq: 0.1, mul: 20);
	//env = EnvGen.ar(Env([0,1],[5]));
	//salida = bpf*env;
	//salida = bpf*EnvGen.ar(Env.cutoff(1), gate, doneAction:2);
	pan = Pan4.ar(in: bpf, xpos: lfn1, ypos: lfn2);
	Out.ar(0, pan);
}).add;
)

~bandpass = Synth(\bandpass)
~bandpass.set(\freq1, 1)
~bandpass.set(\freq2, 1)


(
j=OSCdef(\museOsca, {|msg|
	var delta1, delta2, delta3, delta4, delta5;
	msg.postln;
	delta1 = msg[1].linlin(0.1,0.9,0.5,10);
	delta2 = msg[1].linlin(0.1,0.9,5,25);
	delta3 = msg[1].linlin(0.1,0.9,1,50);
	delta4 = msg[1].linlin(0.1,0.9,10,10);
	delta5 = msg[1].linlin(0.1,0.9,100,1000);
	~bandpass.set(\freq1, delta1);
	~bandpass.set(\freq2, delta2);
	~bandpass.set(\range1, delta3);
	~bandpass.set(\range2, delta4);
	~bandpass.set(\range2, delta5);
},'/muse/elements/alpha_relative')
)

(
SynthDef(\bandpass1, {| saw, pan, out, xpos = 1, ypos = 1, frec = 450, freq1 = 4, freq2 = 8, range1 = 1, range2 = 10 env, gate = 1, salida, bpf|
	var lfn1 = LFNoise2.kr(freq1), lfn2 = LFNoise2.kr(freq2);
	saw = Saw.ar( frec, mul: LFPulse.kr(freq: LFNoise1.kr(freq1).range(range1, range2), width: 0.1));
	bpf = BPF.ar(in: saw, freq: lfn1.range(500, 2500), rq: 0.1, mul: 20);
	//env = EnvGen.ar(Env([0,1],[5]));
	//salida = bpf*env;
	//salida = bpf*EnvGen.ar(Env.cutoff(1), gate, doneAction:2);
	pan = Pan4.ar(in: bpf, xpos: lfn1, ypos: lfn2);
	Out.ar(0, pan);
}).add;
)

~bandpass1 = Synth(\bandpass1)
~bandpass.set(\freq1, 1)
~bandpass.set(\freq2, 1)


(
j=OSCdef(\museOsca, {|msg|
	var delta1, delta2, delta3, delta4, delta5;
	msg.postln;
	delta1 = msg[1].linlin(0.1,0.9,0.5,10);
	delta2 = msg[1].linlin(0.1,0.9,5,25);
	delta3 = msg[1].linlin(0.1,0.9,1,50);
	delta4 = msg[1].linlin(0.1,0.9,10,10);
	delta5 = msg[1].linlin(0.1,0.9,300,13000);
	~bandpass1.set(\freq1, delta1);
	~bandpass1.set(\freq2, delta2);
	~bandpass1.set(\range1, delta3);
	~bandpass1.set(\range2, delta4);
	~bandpass1.set(\range2, delta5);
},'/muse/elements/alpha_relative')
)
