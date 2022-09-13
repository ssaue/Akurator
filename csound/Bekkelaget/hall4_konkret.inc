instr Hall4_konkret
		iID = p4
		iFilLen filelen p5
		p3	= iFilLen
		ichn filenchnls  p5	;check number of channels
		
		iChannel random 1.0, 5.99
		iChannel = int(iChannel)

		if (gkStop[iID] < 1) kgoto continue
				turnoff

continue: 
		krel init 0	
		krel release
		if (krel < 1) kgoto cont
			 ktrig init 1
			 OSCsend	ktrig, "127.0.0.1", giOSCsend, "/finished", "i", iID
			 ktrig = 0

cont:
		kamp = gkVol[iID] * gkFade[iID] * gkMVol[iID] * gkMFade[iID] * 0.5
		String sprintfk "hall_%d", iChannel

		if (ichn == 1) then
			;mono signal
			aSnd soundin p5
			denorm aSnd
			aSnd = kamp * aSnd
			chnmix aSnd, String
		else
			;stereo signal
			a1,a2 soundin p5
			denorm a1,a2
			aSnd = kamp * a1 + kamp * a2
			chnmix aSnd, String
		endif

endin
