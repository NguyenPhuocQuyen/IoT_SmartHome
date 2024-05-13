//Load

function loaddata() {
  //Đèn
  var firebaseRef = firebase.database().ref().child("Led").child("Led1Status");
  // Attach a listener for changes to the data
  firebaseRef.on("value", function (snapshot) {
    var ledStatus = snapshot.val(); // Get the value of the snapshot
    console.log("Led1Status:", ledStatus); // Log the value to the console
    var Led1Status = document.getElementById("toggle1");
    Led1Status.checked = ledStatus == 1;
    console.log("Led1Status:", Led1Status.checked);
  });
  var firebaseRef = firebase.database().ref().child("Led").child("Led2Status");
  // Attach a listener for changes to the data
  firebaseRef.on("value", function (snapshot) {
    var ledStatus = snapshot.val(); // Get the value of the snapshot
    var Led2Status = document.getElementById("toggle2");
    Led2Status.checked = ledStatus == 1;
    console.log("Led2Status:", ledStatus); // Log the value to the console
  });
  var firebaseRef = firebase.database().ref().child("Led").child("Led3Status");
  // Attach a listener for changes to the data
  firebaseRef.on("value", function (snapshot) {
    var ledStatus = snapshot.val(); // Get the value of the snapshot
    var Led3Status = document.getElementById("toggle3");
    Led3Status.checked = ledStatus == 1;
    console.log("Led3Status:", ledStatus); // Log the value to the console
  });
  var firebaseRef = firebase.database().ref().child("Led").child("Led4Status");
  // Attach a listener for changes to the data
  firebaseRef.on("value", function (snapshot) {
    var ledStatus = snapshot.val(); // Get the value of the snapshot
    var Led4Status = document.getElementById("toggle4");
    Led4Status.checked = ledStatus == 1;
    console.log("Led4Status:", ledStatus); // Log the value to the console
  });

  //Quạt
  var firebaseRef = firebase
    .database()
    .ref()
    .child("Span")
    .child("Span1Status");
  // Attach a listener for changes to the data
  firebaseRef.on("value", function (snapshot) {
    var SpanStatus = snapshot.val(); // Get the value of the snapshot
    var Span1Status = document.getElementById("toggleFan1");
    Span1Status.checked = SpanStatus == 1;
    console.log("Quat1Status:", SpanStatus); // Log the value to the console
  });

  //Rèm
  var firebaseRef = firebase.database().ref().child("Rem").child("Rem1Status");
  // Attach a listener for changes to the data
  firebaseRef.on("value", function (snapshot) {
    var rem1Status = snapshot.val(); // Get the value of the snapshot
    var Rem1Status = document.getElementById("toggleRem1");
    Rem1Status.checked = rem1Status == 1;
    console.log("Rem1Status:", Rem1Status.checked);
  });
  var firebaseRef = firebase.database().ref().child("Rem").child("Rem2Status");
  // Attach a listener for changes to the data
  firebaseRef.on("value", function (snapshot) {
    var rem2Status = snapshot.val(); // Get the value of the snapshot
    var Rem2Status = document.getElementById("toggleRem2");
    Rem2Status.checked = rem2Status == 1;
    console.log("Rem2Status:", Rem2Status.checked);
  });
  //Cửa
  var firebaseRef = firebase.database().ref().child("Cua").child("Cua1Status");
  // Attach a listener for changes to the data
  firebaseRef.on("value", function (snapshot) {
    var cua1Status = snapshot.val(); // Get the value of the snapshot
    var Cua1Status = document.getElementById("toggleCua1");
    Cua1Status.checked = cua1Status == 1 ;
    console.log("Cua1Status:", Cua1Status.checked);
  });

  //Khí ga
  var firebaseRef = firebase
    .database()
    .ref()
    .child("Gassensor")
    .child("Notice");
  firebaseRef.on("value", function (snapshot) {
    var noticeContainer = document.getElementById("gas-value");
    var noticeValue = snapshot.val();
    // Update the HTML element with the new value
    noticeContainer.innerText = noticeValue;
  });
  //Độ ẩm
  var firebaseRef = firebase
    .database()
    .ref()
    .child("DHT11Sensor")
    .child("Humi");
  firebaseRef.on("value", function (snapshot) {
    var noticeContainer = document.getElementById("humi-value");
    var noticeValue = snapshot.val();
    // Update the HTML element with the new value
    noticeContainer.innerText = noticeValue + "%";
  });
  //Nhiệt độ
  var firebaseRef = firebase
    .database()
    .ref()
    .child("DHT11Sensor")
    .child("Temp");
  firebaseRef.on("value", function (snapshot) {
    var noticeContainer = document.getElementById("temp-value");
    var noticeValue = snapshot.val();
    // Update the HTML element with the new value
    noticeContainer.innerText = noticeValue + "°C";
  });
}
loaddata();
