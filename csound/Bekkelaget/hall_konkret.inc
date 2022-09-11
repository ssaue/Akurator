instr Hall_konkret
		iID = p4
		iFilLen filelen p5
		p3	= iFilLen
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
		kamp = gkVol[iID] * gkFade[iID] * gkMVol[iID] * gkMFade[iID]
		aSnd soundin p5
		denorm aSnd

		; p6 determines the hall the sound should play in		
		kChannel = p6
		if (kChannel > 3.5) then
			; Hall 4 contains 5 channels 4 - 8
			kChannel random 4.0, 8.99
		endif
	
		String sprintfk "hall_%d", int(kChannel)
		chnmix		aSnd, String

endin
