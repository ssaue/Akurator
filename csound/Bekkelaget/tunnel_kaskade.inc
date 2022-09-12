instr Tunnel_kaskade
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
		kamp = gkVol[iID] * gkFade[iID] * gkMVol[iID] * gkMFade[iID] * 0.5
		a1,a2 soundin p5
		denorm a1, a2
		aSnd = kamp * a1 + kamp * a2

		kAzim      line       0, p3, 175
		a1, a2, a3, a4, a5, a6, a7, a8  vbap aSnd, kAzim, 0, 0, 1

		chnmix		a1, "tunnel_1"
		chnmix		a2, "tunnel_2"
		chnmix		a3, "tunnel_3"
		chnmix		a4, "tunnel_4"
		chnmix		a5, "tunnel_5"
		chnmix		a6, "tunnel_6"
		chnmix		a7, "tunnel_7"
		chnmix		a8, "tunnel_8"

endin
