<img src="https://i.imgur.com/IclH4mR.png" align="center" title="Robot" width="100%">
<h1 align="center">
  PD Line Follower
</h1>

<h3 allign="right">
  Description
</h3>
<p>
  This code has been calibrated and written specifically for the 
  <a href="https://www.pololu.com/product/2151">m3pi</a> robot but with minor 
  modifications to data acquisition and recalibration of constants it should work 
  for any other (similar) robot.
</p>

<h3 allign="right">
  Explanation
</h3>
<p>
  The controller works by calculating a line position based on data received from 
  5 bottom mounted reflectance sensors then feeding this position into the 
  <a href="https://en.wikipedia.org/wiki/PID_controller">PD 
  control loop</a> which calculates a control variable, namely the speed delta. 
  Using this value, the left and right motor speeds are determined and the whole 
  process is repeated.
</p>

<h3 allign="right">
  Additional functionality:
</h3>
<ul>
  <li>Detect and stop at a T junction</li>
  <li>Right turn bias to avoid misdetection of adjacent lines</li>
</ul>
