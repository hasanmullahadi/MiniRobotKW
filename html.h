/*
 * This code has been based on work of https://github.com/KrisKasprzak/ESP32_WebPage
 * you can also go to his YouTube channel and see the way he did this : 
 * https://www.youtube.com/watch?v=pL3dhGtmcMY&t=1029s
 * 
 */

#ifndef __html_h__
#define __html_h__

const char PAGE_MAIN[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<title>MinRobotKW V1.02</title>

  <style>
    table {
      position: relative;
      width:100%;
      border-spacing: 0px;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      height: 20px;
      padding: 3px 15px;
      background-color: #343a40;
      color: #FFFFFF !important;
      }
    td {
      height: 20px;
       padding: 3px 15px;
    }
    .tabledata {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height:   25px;
      border-radius: 5px;
      color: #FFFFFF;
      line-height: 20px;
      transition: all 200ms ease-in-out;
      background-color: #00AA00;
    }
    .fanrpmslider {
      width: 30%;
      height: 55px;
      outline: none;
      height: 25px;
    }
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #FFF;
      color: #000000;
      border-bottom: 5px solid #293578;
    }
    .fixed-top {
      position: fixed;
      top: 0;
      right: 0;
      left: 0;
      z-index: 1030;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
   .navheading {
     position: fixed;
     left: 60%;
     height: 50px;
     font-family: "Verdana", "Arial", sans-serif;
     font-size: 20px;
     font-weight: bold;
     line-height: 20px;
     padding-right: 20px;
   }
   .navdata {
      justify-content: flex-end;
      position: fixed;
      left: 70%;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      line-height: 20px;
      padding-right: 20px;
   }
    .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 32px;
      line-height: 50px;
      padding: 20px 10px 0px 10px;
      color: #000000;
    }
    .heading {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: normal;
      font-size: 28px;
      text-align: left;
    }
  
    .btn {
      background-color: #444444;
      border: none;
      color: white;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
    }
    .foot {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      position: relative;
      height:   30px;
      text-align: center;   
      color: #AAAAAA;
      line-height: 20px;
    }
    .container {
      max-width: 1800px;
      margin: 0 auto;
    }
    table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }
    
  </style>
<head>
  <title>MiniRobot V1.02</title>
</head>
  <body style="background-color: #efefef" onload="process()">
  
    <header>
      <div class="navbar fixed-top">
          <div class="container">
            <div class="navtitle">Mini Robot</div>
            <div class="navdata" id = "date">mm/dd/yyyy</div>
            <div class="navheading">DATE</div><br>
            <div class="navdata" id = "time">00:00:00</div>
            <div class="navheading">TIME</div>
            
          </div>
      </div>
    </header>
  
    <main class="container" style="margin-top:70px">
      <div class="category">Sensor Readings</div>
      <div style="border-radius: 10px !important;">
      <table style="width:50%">
      <colgroup>
        <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
        <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
       
      </colgroup>
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
     
      <tr>
        <th colspan="1"><div class="heading">Sensor</div></th>
        <th colspan="1"><div class="heading">Value</div></th>
        
      </tr>
      <tr>
        <td><div class="bodytext">Distance</div></td>
        <td><div class="tabledata" id = "v0"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">IR</div></td>
        <td><div class="tabledata" id = "v1"></div></td>
      </tr>
       <tr>
        <td><div class="bodytext">Mode</div></td>
        <td><div class="tabledata" id = "v2"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">Direction</div></td>
        <td><div class="tabledata" id = "v3"></div></td>
      </tr>
    </table>
    </div>
    <br>
    <div class="category">Mode Selection</div>
    <br>
    <table style="width:50%">
    <colgroup>
      <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
      <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
     
    </colgroup>
    <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
    <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
    <tr>
      <td><div class="bodytext">Follow Line</div></td>
      <td><button type="button" class = "btn" id = "btn0" onclick="ButtonPress0()">Toggle</button></div></td>
    </tr>
    
    <tr>
     <td><div class="bodytext">Obstacle</div></td>
    <td><button type="button" class = "btn" id = "btn1" onclick="ButtonPress1()">Toggle</button></div> </td>
    </tr>
    <tr>
      <td><div class="bodytext">Free Form</div></td>
       <td><button type="button" class = "btn" id = "btn2" onclick="ButtonPress2()">Toggle</button></div> </td>
    </tr>
     </table>
    <br>
    <br>
        <div class="category">Free Mode Controls</div>
    <br>
    <table style="width:50%">
    <colgroup>
      <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
      <col span="1" style="background-color:rgb(200,200,200); width: 20%; color:#000000 ;">        
      <col span="1" style="background-color:rgb(180,180,180); width: 20%; color:#000000 ;">
     
    </colgroup>
    <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
    <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
    <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
   <tr>
    <td></td>
    <td> 
    <button type="button" class = "btn" id = "btn4" onclick="ButtonPress4()">Toggle</button>
    </div></td>
    <td></td>
    </tr>

    <tr>
    <td>
      
    <button type="button" class = "btn" id = "btn6" onclick="ButtonPress6()">Toggle</button>
    </div>
    </td>
    <td>
       
    <button type="button" class = "btn" id = "btn3" onclick="ButtonPress3()">Toggle</button>
    </div>
    </td>

    <td>
           
    <button type="button" class = "btn" id = "btn7" onclick="ButtonPress7()">Toggle</button>
    </div>
    </td>
    </tr>

   <tr>
   <td>
   </td>
    <td>
     
    <button type="button" class = "btn" id = "btn5" onclick="ButtonPress5()">Toggle</button>
    </div>
   </td>
    <td>
   </td>
   </tr>
  
   

   

   </table>
    <br>
    <br>
    <div class="bodytext">Timer Control (x100ms: <span id="timeVal"></span>)</div>
    <br>
    <input type="range" class="fanrpmslider" min="0" max="100" value = "0" width = "0%" oninput="UpdateSlider(this.value)"/>
    <br>
    <br>
  </main>

  <footer div class="foot" id = "temp" >ESP32 Web Page for Mini Robot Ver 1.02 </div></footer>
  
  </body>


  <script type = "text/javascript">
  
    // global variable visible to all java functions
    var xmlHttp=createXmlHttpObject();

    // function to create XML object
    function createXmlHttpObject(){
      if(window.XMLHttpRequest){
        xmlHttp=new XMLHttpRequest();
      }
      else{
        xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
      }
      return xmlHttp;
    }

    // function to handle button press from HTML code above
    // and send a processing string back to server
    // this processing string is use in the .on method
    function ButtonPress0() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      // if you want to handle an immediate reply (like status from the ESP
      // handling of the button press use this code
      // since this button status from the ESP is in the main XML code
      // we don't need this
      // remember that if you want immediate processing feedbac you must send it
      // in the ESP handling function and here
      /*
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          message = this.responseText;
          // update some HTML data
        }
      }
      */
       
      xhttp.open("PUT", "BUTTON_0", false);
      xhttp.send();
    }


    // function to handle button press from HTML code above
    // and send a processing string back to server
    // this processing string is use in the .on method
    function ButtonPress1() {
      var xhttp = new XMLHttpRequest(); 
      /*
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("button1").innerHTML = this.responseText;
        }
      }
      */
      xhttp.open("PUT", "BUTTON_1", false);
      xhttp.send(); 
    }
    
    function ButtonPress2() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_2", false);
      xhttp.send(); 
    }
    function ButtonPress3() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_3", false);
      xhttp.send(); 
    }
    function ButtonPress4() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_4", false);
      xhttp.send(); 
    }    
    function ButtonPress5() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_5", false);
      xhttp.send(); 
    }    
    function ButtonPress6() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_6", false);
      xhttp.send(); 
    }  
    function ButtonPress7() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_7", false);
      xhttp.send(); 
    }          
    function UpdateSlider(value) {
      var xhttp = new XMLHttpRequest();
      // this time i want immediate feedback to the fan speed
      // yea yea yea i realize i'm computing fan speed but the point
      // is how to give immediate feedback
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          // update the web based on reply from  ESP
          document.getElementById("timeVal").innerHTML=this.responseText;
        }
      }
      // this syntax is really weird the ? is a delimiter
      // first arg UPDATE_SLIDER is use in the .on method
      // server.on("/UPDATE_SLIDER", UpdateSlider);
      // then the second arg VALUE is use in the processing function
      // String t_state = server.arg("VALUE");
      // then + the controls value property
      xhttp.open("PUT", "UPDATE_SLIDER?VALUE="+value, true);
      xhttp.send();
    }

    // function to handle the response from the ESP
    function response(){
      var message;
      var barwidth;
      var currentsensor;
      var xmlResponse;
      var xmldoc;
      var dt = new Date();
      var color = "#e8e8e8";
     
      // get the xml stream
      xmlResponse=xmlHttp.responseXML;
  
      // get host date and time
      document.getElementById("time").innerHTML = dt.toLocaleTimeString();
      document.getElementById("date").innerHTML = dt.toLocaleDateString();
  
      // v0
      xmldoc = xmlResponse.getElementsByTagName("V0"); 
      message = xmldoc[0].firstChild.nodeValue;
      
      if (message < 5){
      color = "#aa0000";
      }
      else {
        color = "#0000aa";
      }
      
      barwidth = message / 40.95;
      document.getElementById("v0").innerHTML=message;
      document.getElementById("v0").style.width=(barwidth+"%");
      // if you want to use global color set above in <style> section
      // other wise uncomment and let the value dictate the color
      document.getElementById("v0").style.backgroundColor=color;
     
      // v1
      xmldoc = xmlResponse.getElementsByTagName("V1");
      message = xmldoc[0].firstChild.nodeValue;
      if (message > 2048){
      color = "#aa0000";
      }
      else {
        color = "#0000aa";
      }
      document.getElementById("v1").innerHTML=message;
      width = message / 40.95;
      document.getElementById("v1").style.width=(width+"%");
      document.getElementById("v1").style.backgroundColor=color;

  
      xmldoc = xmlResponse.getElementsByTagName("V2");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("v2").innerHTML=message;
      if (message == "FREE"){
        document.getElementById("btn0").innerHTML="ON";
        document.getElementById("btn1").innerHTML="ON";
        document.getElementById("btn2").innerHTML="OFF";
      }
      else if (message == "FOLLOW") {
        document.getElementById("btn0").innerHTML="OFF";
        document.getElementById("btn1").innerHTML="ON";
        document.getElementById("btn2").innerHTML="ON";
      }
      else if (message == "OBSTACLE") {
        document.getElementById("btn0").innerHTML="ON";
        document.getElementById("btn1").innerHTML="OFF";
        document.getElementById("btn2").innerHTML="ON";
      }



      // Operation Mode   

      // Current Robot Direction    
      xmldoc = xmlResponse.getElementsByTagName("V3");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("v3").style.backgroundColor="rgb(200,200,200)";
      // update the text in the table
      if (message == "STOP"){
        document.getElementById("v3").innerHTML="STOP";
        document.getElementById("btn3").innerHTML="[STOP]";
        document.getElementById("btn3").style.color="#008000"; 
        document.getElementById("btn4").innerHTML="FORWARD"; 
        document.getElementById("btn4").style.color="#edeff2"; 
        document.getElementById("btn5").innerHTML="REVERSE";
        document.getElementById("btn5").style.color="#edeff2";
        document.getElementById("btn6").innerHTML="LEFT";
        document.getElementById("btn6").style.color="#edeff2"; 
        document.getElementById("btn7").innerHTML="RIGHT";
        document.getElementById("btn7").style.color="#edeff2"
        document.getElementById("v3").style.color="#0000AA"; 
      }
      else if (message == "FORWARD") {
        document.getElementById("v3").innerHTML="FORWARD";
        document.getElementById("btn3").innerHTML="STOP";
        document.getElementById("btn3").style.color="#edeff2"; 
        document.getElementById("btn4").innerHTML="[FORWARD]"; 
        document.getElementById("btn4").style.color="#ed091c";
        document.getElementById("btn5").innerHTML="REVERSE";
        document.getElementById("btn5").style.color="#edeff2";
        document.getElementById("btn6").innerHTML="LEFT";
        document.getElementById("btn6").style.color="#edeff2"; 
        document.getElementById("btn7").innerHTML="RIGHT";
        document.getElementById("btn7").style.color="#edeff2"
        document.getElementById("v3").style.color="#0000AA"; 
      }
       else if (message == "REVERSE") {
         document.getElementById("v3").innerHTML="REVERSE";
        document.getElementById("btn3").innerHTML="STOP";
        document.getElementById("btn3").style.color="#edeff2"; 
        document.getElementById("btn4").innerHTML="FORWARD"; //#ed091c
        document.getElementById("btn4").style.color="#edeff2";
        document.getElementById("btn5").innerHTML="[REVERSE]";
        document.getElementById("btn5").style.color="#ed091c";
        document.getElementById("btn6").innerHTML="LEFT";
        document.getElementById("btn6").style.color="#edeff2"; 
        document.getElementById("btn7").innerHTML="RIGHT";
        document.getElementById("btn7").style.color="#edeff2"

        document.getElementById("v3").style.color="#0000AA"; 
      }

       else if (message == "LEFT") {
        document.getElementById("v3").innerHTML="LEFT";
        document.getElementById("btn3").innerHTML="STOP";
        document.getElementById("btn3").style.color="#edeff2"; 
        document.getElementById("btn4").innerHTML="FORWARD"; //#ed091c
        document.getElementById("btn4").style.color="#edeff2";
        document.getElementById("btn5").innerHTML="REVERSE";
        document.getElementById("btn5").style.color="#edeff2";
        document.getElementById("btn6").innerHTML="[LEFT]";
        document.getElementById("btn6").style.color="#ed091c"; 
        document.getElementById("btn7").innerHTML="RIGHT";
        document.getElementById("btn7").style.color="#edeff2"
        document.getElementById("v3").style.color="#0000AA"; 
      }

       else if (message == "RIGHT") {
        document.getElementById("v3").innerHTML="RIGHT";
        document.getElementById("btn3").innerHTML="STOP";
        document.getElementById("btn3").style.color="#edeff2"; 
        document.getElementById("btn4").innerHTML="FORWARD"; //#ed091c
        document.getElementById("btn4").style.color="#edeff2";
        document.getElementById("btn5").innerHTML="REVERSE";
        document.getElementById("btn5").style.color="#edeff2";
        document.getElementById("btn6").innerHTML="LEFT";
        document.getElementById("btn6").style.color="#edeff2"; 
        document.getElementById("btn7").innerHTML="[RIGHT]";
        document.getElementById("btn7").style.color="#ed091c"
        document.getElementById("v3").style.color="#0000AA"; 
      }


      


      
     }
  
    // general processing code for the web page to ask for an XML steam
    // this is actually why you need to keep sending data to the page to 
    // force this call with stuff like this
    // server.on("/xml", SendXML);
    // otherwise the page will not request XML from the ESP, and updates will not happen
    function process(){
     
     if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
        xmlHttp.open("PUT","xml",true);
        xmlHttp.onreadystatechange=response;
        xmlHttp.send(null);
      }       
        // you may have to play with this value, big pages need more porcessing time, and hence
        // a longer timeout
        setTimeout("process()",100);
    }
  
  
  </script>

</html>
)rawliteral";

#endif
