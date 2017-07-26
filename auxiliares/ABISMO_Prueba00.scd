s.boot;
s.meter(4);
s.options.device = "ASIO : UMC ASIO Driver"
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


///////////////// IDEA! hacer un movimiento que sea solo el sonido de los corazones.. este podria ser el primer o ultimo movimiento...



///////////// ----------------------------  TDEF MAESTRO -------------------- /////////////////////////////


/*

Orden de Sensaciones:

A Entendimiento/Tranquilidad
01 Expectativa
02 Miedo
03 Asombro
04 Euforia
05 Tristeza/Soledad
06 Abismo
07 Felicidad
08 Reconocimiento
B Proximidad


*/

(
Tdef(\Opcion_A, {
	Tdef(\Entendimiento00).play;
	90.wait;
	Tdef(\Expectativa00).play;//Min 00:00 - 01:30
	90.wait;
	Tdef(\Miedo00).play;//Min 01:30 - 03:00
	90.wait;
	Tdef(\Asombro00).play;//Min 03:00 - 04:30
	90.wait;
	Tdef(\Euforia00).play;//Min 04:30 - 06:00
	90.wait;
	Tdef(\Soledad00).play;//Min 06:00 - 07:30
	90.wait;
	Tdef(\Abismo00).play;//Min 07:30 - 09:00
	90.wait;
	Tdef(\Felicidad00).play;//Min 09:00 - 10:30
	90.wait;
	Tdef(\Reconocimiento00).play;//Min 10:30 - 12:30
	90.wait;
	"ABISMO // PRÓXIMO".postln;
}
);
)

Tdef(\Opcion_A).play;




(
Tdef(\Opcion_B, {
	Tdef(\Entendimiento00).play;
	90.wait;
	Tdef(\Expectativa00).play;//Min 00:00 - 01:30
	90.wait;
	Tdef(\Miedo01).play;//Min 01:30 - 03:00
	90.wait;
	Tdef(\Asombro00).play;//Min 03:00 - 04:30
	90.wait;
	Tdef(\Euforia01).play;//Min 04:30 - 06:00
	90.wait;
	Tdef(\Soledad01).play;//Min 06:00 - 07:30
	90.wait;
	Tdef(\Abismo01).play;//Min 07:30 - 09:00
	90.wait;
	Tdef(\Felicidad00).play;//Min 09:00 - 10:30
	90.wait;
	Tdef(\Reconocimiento00).play;//Min 10:30 - 12:30
	90.wait;
	"ABISMO // PRÓXIMO".postln;
}
);
)

Tdef(\Opcion_B).play;






//Entendimiento

Tdef(\Expectativa00).play;

Tdef(\Expectativa01).play;

Tdef(\Miedo00).play;

Tdef(\Miedo01).play;

Tdef(\Asombro00).play;

Tdef(\Euforia00).play;

Tdef(\Euforia01).play;

Tdef(\Soledad00).play;

Tdef(\Soledad01).play;

Tdef(\Abismo00).play;

Tdef(\Abismo01).play;

Tdef(\Felicidad00).play;

Tdef(\Reconocimiento00).play;


(
Tdef(\Abismo01, {
	//s.record;
	1.wait;
	~resonz00 = Synth(\resonz00);
	5.wait;
	~resonz01 = Synth(\resonz01);
	10.wait;
	(
		x=OSCdef(\museOscx, {|msg|
			var freq;
			msg.postln;
			if(msg[1] == 1, // BLINK DEL SENSOR 1
				if(msg[3]==[1,2,3].choose,
					{"blink 1".post;
						~choose = Synth([\klang00, \klang01, \klang02, \klang03, \klang04, \klang05].choose);
					}
				),
				if(msg[1] == 2,
					{
						if(msg[3]==[1,2,3].choose,
							{"blink 1".post;
								~choose = Synth([\klang00, \klang01, \klang02, \klang03, \klang04, \klang05].choose);
							}
						)
					}
				)
			)
			/*					if(msg[1]==1,
			{"blink".post;
			~canto.set(\bus, [0, 1, 2, 3].choose);
			~canto1.set(\dir, [70, 80, 90, 100].choose);
			~canto1.set(\bus, [0, 1, 2, 3].choose);
			~canto2.set(\bus, [0, 1, 2, 3].choose);
			}
			)*/
		},
		'/artifacts'
		);
	);
	(
		~pulsos=OSCdef(\sensorPulse, {|msg|
			var pulso1, pulso2;
			msg.postln;
			if(msg[1] == 1,
				{ postln("Sensor Pulso 01");
					{Out.ar(0,WhiteNoise.ar(0.05)+SinOsc.ar([80,86,0,0],0,0.75)*EnvGen.ar(Env.perc(0.005), doneAction:2))}.play;
					pulso1 = msg[2];
				},
				if(msg[1] == 2,
					{ postln("Sensor Pulso 02");
						{Out.ar(0,WhiteNoise.ar(0.05)+SinOsc.ar([0,0,80,86],0,0.75)*EnvGen.ar(Env.perc(0.005), doneAction:2))}.play;
						pulso2 = msg[2];
					}
				)
			)
		},
		'/pulse'
		);
	);
	(
		~gsrs=OSCdef(\sensorGSR, {|msg|
			var gsr1, gsr2;
			msg.postln;
			if(msg[1] == 1,
				{ postln("Sensor GSR 01");
					//askjdgh.set(freq, 100+msg[2]);
					gsr1 = msg[2];
				},
				if(msg[1] == 2,
					{ postln("Sensor GSR 02");
						gsr2 = msg[2];
					}
				)
			)
		},
		'/gsr'
		);
	)

	65.wait;
	x.free;
	~resonz00.set(\gate, 0);
	2.wait;
	~resonz01.set(\gate, 0);
	10.wait;
	//s.stop.record;
	"FIN".postln;
});
)












