# VacuumCleaner-simulation-Swift-act-intern
- [Description](#Description)
- [Context Diagram](#Context-Diagram)
- [IDE](#IDE)
- [Control Speed](#Control-Speed)
- [Demo](#Demo)

## Description
<p>⚡Here I simulate Vaccuum cleaner functionality as when <strong>power on</strong> power of motor go from low power to high power gradually </p>
<p>⚡🎛can control speed (Low  , meduim & High ) and know bag that store dust is full of when led of pressure be on and speed of motor reduce gradually to low </p>

## Context Diagram
<p align="center" >
  <p> Fig 1</p>
  <img src="https://github.com/HESHAM47GAMAL/VacuumCleaner-simulation-Swift-act-intern/blob/main/img/Context%20Diagram.png">
  <p> Fig 2</p>
  <img src="https://github.com/HESHAM47GAMAL/VacuumCleaner-simulation-Swift-act-intern/blob/main/img/flow.png" />
  </p>
  <p> fig 3 here switch mood during stability at same speed and switch from speed to another</p>
  <p>
  <img src="https://github.com/HESHAM47GAMAL/VacuumCleaner-simulation-Swift-act-intern/blob/main/img/switch_mood.png" />
  </p>
  
 ## IDE 
 <p> Keil uVision5 </p>
 
 ## Control Speed
 <p> ⚡here will explain how control speed to motors as power come from sin wave 👀always look at contex diagram <p/>
 <p> ⚡power come from AC power source go through zero crossing detector (ZCD) as work crystal </p>
 <p> ⚡A triac is a type of thyristor, a semiconductor component that is used for AC switching applications. It is a three-terminal device that is used to control the flow of electrical current in AC circuits</p>
 <p> ⚡next image will visualize better and control of speed of motor depend on time of firing (give high to motor) and time that I have from 0 to 180 degree every degree take specific time and firing every specific time mean specific degree and at this degree motor will be high until 180 degree and will be high again with next fire </p>
 <p>
  <img src="https://github.com/HESHAM47GAMAL/VacuumCleaner-simulation-Swift-act-intern/blob/main/img/control_speed_to%20_motor.png" />
</p>
 
 
 
 ## Demo 
 <p> ⚡when <strong>power on</strong> start with 10 % of power and go to 50% power  by applying <strong>Soft switch</strong> </p>
 <p>
  <img src="https://github.com/HESHAM47GAMAL/VacuumCleaner-simulation-Swift-act-intern/blob/main/gif/video_p1.gif" />
  </p>
  
  <p> ⚡when get target apply <strong>Harmonic reduction</strong> for mid speed (90 degree) </p> 
  <p>
  <img src="https://github.com/HESHAM47GAMAL/VacuumCleaner-simulation-Swift-act-intern/blob/main/gif/video_p2.gif" />
  </p>
  
   <p> ⚡when <strong>press plus button</strong> go from 50 % of power to 90% power  by applying <strong>Soft switch</strong> </p>
 <p>
  <img src="https://github.com/HESHAM47GAMAL/VacuumCleaner-simulation-Swift-act-intern/blob/main/gif/video_p1.gif" />
  </p>
  
   <p> ⚡when get target apply <strong>Harmonic reduction</strong> for high speed (10 degree) </p> 
  <p>
  <img src="https://github.com/HESHAM47GAMAL/VacuumCleaner-simulation-Swift-act-intern/blob/main/gif/video_p4.gif" />
  </p>
