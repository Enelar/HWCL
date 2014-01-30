SEQUENCE AIR (HPM; POINT AIR) -- hpm09
  
EXTERNAL !BOX 
EXTERNAL FRCA820, PI820
  
LOCAL Pb          AT !BOX.NN(11)    -- аюпнлерпхвеяйне дюбкемхе 
  
LOCAL F        at NN(01)        -- пюяунд %
LOCAL Q        at NN(02)        -- пюяунд л3/в   
LOCAL Flow     at NN(03)        -- пюяунд я мювюкю ясрнй рнмм  
LOCAL LastFlow AT NN(04)        -- пюяунд опнькшу ясрнй рнмм   
LOCAL P        at NN(05)
LOCAL PI       at NN(06) 
LOCAL E        at NN(07)        -- йнщттхжхемр пюяьхпемхъ
LOCAL CQ       at NN(10)
LOCAL S        AT NN(11)
LOCAL S1       at NN(12)
LOCAL S2       at NN(13)
LOCAL Re       at NN(14)
LOCAL Kre      at NN(15)
LOCAL DATE     at NN(80)    
  
LOCAL T = 115
LOCAL X = 1.41 
  
LOCAL K=1.01                     -- йнщттхжхемр яфюрхъ
LOCAL D20 = 145.83
LOCAL D = 207.24
LOCAL DPN = 1000
LOCAL KT = 1.0015
LOCAL PN = 1.2044                -- ОКНРМНЯРЭ ОПХ МНПЛaКЭМШУ СЯКНБХЪУ, йц/л3 
LOCAL M = 2.3E-6 
LOCAL MD=0.4967
LOCAL A=0.6957
LOCAL B=0.00139
LOCAL C=0.6909
  
PHASE P1
 STEP S1
  
SET C=1+1
SET C=2+2*2
SET C=(0.5959+0.0312*MD**1.05-0.184*MD**4)/SQRT(1-MD**2)  -- DEBUG
  SET DATE=!BOX.DAY 
  SET FLOW=0.0
L1: SET F=0.0  
--  SET MD=(D20*KT/D)**2
--  SET B=0.0029*MD**1.25/SQRT(1-MD**2) 
--  SET C=(0.5959+0.0312*MD**1.05-0.184*MD**4)/SQRT(1-MD**2)
--  SET A=(B+C)*1.004*1.0045
 
L2: IF FRCA820.BADPVFL OR FRCA820.PVP<2 OR FRCA820.PVP>100 THEN (SET F,Q = 0;GOTO L4) 
    IF PI820.BADPVFL OR PI820.PVP<0 OR PI820.PVP>100 THEN GOTO L3
    SET  PI=PI820.PV
L3: SET  F=FRCA820.PVP
    SET  Pb=!BOX.NN(11)
    SET  P=PI+Pb/735.56 
    SET  CQ=0.2109*D20**2*SQRT(DPN) 
    SET  E=1-(0.41+0.35*MD**2)*((F/100)**2*DPN)/(P*X*10000) 
    SET  Q=CQ*A*E*KT**2*SQRT(P/(T+273.15))*(F/100)/SQRT(PN)/SQRT(K)
    SET  Re=(0.0361*PN*Q)/(D*M) 
    SET  S1=B*Re/(A*1.0E6)
    SET  S2=C*Re/(A*1.0E6)
    SET  S=S1/(S2**1.75) 
    SET  Re=C*Re/(A*(1-S*(1-S*(1-S)**1.75)**1.75)) 
    SET  Kre=(C+B*(1.0E6/Re)**0.75)/(C+B) 
    SET  Q=Q*Kre
  
    SET  Flow=Flow+Q/3600 
  
L4: IF   (!BOX.HOUR<>0) or (!BOX.MINUTE<>0) or (DATE=!BOX.DAY) THEN GOTO L2 
    SET  DATE=!BOX.DAY
    SET  LastFlow=Flow
    SET  Flow=0 
    SEND LOG_ONLY: " бНГДСУ= ",LastFLOW," m3"
    GOTO L2
  
END AIR 
  
