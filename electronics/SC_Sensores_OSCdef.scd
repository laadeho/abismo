(
(
~pulsos=OSCdef(\sensorPulse, {|msg|
	var pulso1, pulso2;
	msg.postln;
	if(msg[1] == 1,
		{ postln("Sensor Pulso 01");
			pulso1 = msg[2];
		},
		if(msg[1] == 2,
			{ postln("Sensor Pulso 02");
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
)