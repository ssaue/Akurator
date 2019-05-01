<CsoundSynthesizer> 
<CsOptions> 
-odac 
</CsOptions> 
<CsInstruments> 
sr = 44100 
nchnls = 1 

gicnt init 1 

instr 1 
icnt active 1001 
print icnt 
if(icnt>0) then	;kill instance of 1001 
turnoff2 1001, 2, 0 
endif 
event "i", 1001, 0, 100 ;start new instace 
turnoff 
endin 

instr 1001 
prints "turned on instance %d!\n", gicnt 
gicnt = gicnt+1 
a1 oscil 10000, 300, 1 
out a1 
endin 

</CsInstruments> 
<CsScore> 
f1 0 1024 10 1 
f0 3600 
i1 0 1 
i1 2 1 
</CsScore> 
</CsoundSynthesizer> 
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>255</r>
  <g>255</g>
  <b>255</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
