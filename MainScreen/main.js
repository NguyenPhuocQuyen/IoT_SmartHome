//Connect Firebase
var firebaseConfig = {
  apiKey: "AIzaSyAj_rp399bQKQNt4bQzyYBhiskIaAyWvHs",
  authDomain: "iotsmarthome-e9c19.firebaseapp.com",
  databaseURL: "https://iotsmarthome-e9c19-default-rtdb.firebaseio.com",
  projectId: "iotsmarthome-e9c19",
  storageBucket: "iotsmarthome-e9c19.appspot.com",
  messagingSenderId: "1090433013367",
  appId: "1:1090433013367:web:ec3c272951c6c550dd1872",
  measurementId: "G-JRK0HKXB4X",
};
// Initialize Firebase
firebase.initializeApp(firebaseConfig);

//Logout
document.addEventListener("DOMContentLoaded", function () {
  // Khai báo logoutButton
  const logoutButton = document.getElementById("logoutButton");

  // Kiểm tra xem logoutButton có tồn tại không
  if (logoutButton) {
    logoutButton.addEventListener("click", function () {
      logout_function();
    });
  }
});
function logout_function() {
  window.location.href = "../LoginScreen/login.html";
}

// Đèn
function toggleButtonClick(numlight) {
  var Led1Status = document.getElementById("toggle" + numlight).checked;
  var firebaseRef = firebase
    .database()
    .ref()
    .child("Led")
    .child("Led" + numlight + "Status");

  if (Led1Status == true) {
    // post to firebase
    firebaseRef.set("1");
  } else {
    firebaseRef.set("0");
  }
}

// // Quạt
function toggleButtonClickFan(numspan) {
  var Span1Status = document.getElementById("toggleFan" + numspan).checked;
  var firebaseRef = firebase
    .database()
    .ref()
    .child("Span")
    .child("Span" + numspan + "Status");

  if (Span1Status == true) {
    // post to firebase
    firebaseRef.set("1");
  } else {
    firebaseRef.set("0");
  }
}

// Rèm
function toggleButtonClickRem(numrem) {
  var Rem1Status = document.getElementById("toggleRem" + numrem).checked;
  var firebaseRef = firebase
    .database()
    .ref()
    .child("Rem")
    .child("Rem" + numrem + "Status");

  if (Rem1Status == true) {
    // post to firebase
    firebaseRef.set("1");
  } else {
    firebaseRef.set("0");
  }
}

// Cửa
function toggleButtonClickCua(numcua) {
  var Cua1Status = document.getElementById("toggleCua" + numcua).checked;
  var firebaseRef = firebase
    .database()
    .ref()
    .child("Cua")
    .child("Cua" + numcua + "Status");

  if (Cua1Status == true) {
    // post to firebase
    firebaseRef.set("1");
  } else {
    firebaseRef.set("0");
  }
}

// Camera
document.addEventListener("DOMContentLoaded", () => {
  const video = document.getElementById("cameraFeed");

  navigator.mediaDevices
    .getUserMedia({ video: true })
    .then((stream) => {
      video.srcObject = stream;
    })
    .catch((error) => {
      console.error("Error accessing the camera: ", error);
    });
});

document.addEventListener("DOMContentLoaded", () => {
  const video = document.getElementById("cameraFeed1");

  navigator.mediaDevices
    .getUserMedia({ video: true })
    .then((stream) => {
      video.srcObject = stream;
    })
    .catch((error) => {
      console.error("Error accessing the camera: ", error);
    });
});
function inforlinh() {
  window.location.href = "../Information/linh.html";
}
function inforthuy() {
  window.location.href = "../Information/thuy.html";
}
function inforphu() {
  window.location.href = "../Information/phu.html";
}
function inforanh() {
  window.location.href = "../Information/anh.html";
}
function inforthanh() {
  window.location.href = "../Information/thanh.html";
}
function inforquyen() {
  window.location.href = "../Information/quyen.html";
}

// Hàm gọi của quạt
function turnonFan() {
  var firebaseRef = firebase
    .database()
    .ref()
    .child("Span")
    .child("Span1Status");
  firebaseRef.set("1");
}
function turnoffFan() {
  var firebaseRef = firebase
    .database()
    .ref()
    .child("Span")
    .child("Span1Status");
  firebaseRef.set("0");
}
//Hàm gọi của cửa
function turnonCua() {
  var firebaseRef = firebase.database().ref().child("Cua").child("Cua1Status");
  firebaseRef.set("1");
}
function turnoffCua() {
  var firebaseRef = firebase.database().ref().child("Cua").child("Cua1Status");
  firebaseRef.set("0");
}
//Hàm gọi của đèn
function turnonDen() {
  var firebaseRef0 = firebase.database().ref().child("Led").child("Led1Status");
  var firebaseRef1 = firebase.database().ref().child("Led").child("Led2Status");
  var firebaseRef2 = firebase.database().ref().child("Led").child("Led3Status");
  var firebaseRef3 = firebase.database().ref().child("Led").child("Led4Status");
  firebaseRef0.set("1");
  firebaseRef1.set("1");
  firebaseRef2.set("1");
  firebaseRef3.set("1");
}
function turnoffDen() {
  var firebaseRef0 = firebase.database().ref().child("Led").child("Led1Status");
  var firebaseRef1 = firebase.database().ref().child("Led").child("Led2Status");
  var firebaseRef2 = firebase.database().ref().child("Led").child("Led3Status");
  var firebaseRef3 = firebase.database().ref().child("Led").child("Led4Status");
  firebaseRef0.set("0");
  firebaseRef1.set("0");
  firebaseRef2.set("0");
  firebaseRef3.set("0");
}
function turnonDen1() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led1Status");
  firebaseRef.set("1");
}
function turnoffDen1() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led1Status");
  firebaseRef.set("0");
}
function turnonDen2() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led2Status");
  firebaseRef.set("1");
}
function turnoffDen2() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led2Status");
  firebaseRef.set("0");
}
function turnonDen3() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led3Status");
  firebaseRef.set("1");
}
function turnoffDen3() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led3Status");
  firebaseRef.set("0");
}
function turnonDen4() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led4Status");
  firebaseRef.set("1");
}
function turnoffDen4() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led1Status");
  firebaseRef.set("0");
}

//Hàm gọi của rèm
function turnonRem1() {
  var firebaseRef = firebase.database().ref().child("Rem").child("Rem1Status");
  firebaseRef.set("1");
}
function turnoffRem1() {
  var firebaseRef = firebase.database().ref().child("Rem").child("Rem1Status");
  firebaseRef.set("0");
}
function turnonRem2() {
  var firebaseRef = firebase.database().ref().child("Rem").child("Rem2Status");
  firebaseRef.set("1");
}
function turnoffRem2() {
  var firebaseRef = firebase.database().ref().child("Rem").child("Rem2Status");
  firebaseRef.set("0");
}

//Hàm nhận diện giọng nói
let recognition;

const voiceCommands = {
  "đăng xuất": logout_function,
  "thông tin linh": inforlinh,
  "thông tin thuỳ": inforthuy,
  "thông tin phú": inforphu,
  "thông tin quyền": inforquyen,
  "thông tin anh": inforanh,
  "thông tin thành": inforthanh,
  "bật quạt": turnonFan,
  "tắt quạt": turnoffFan,
  "mở cửa": turnonCua,
  "đóng cửa": turnoffCua,
  "bật đèn thứ nhất": turnonDen1,
  "tắt đèn thứ nhất": turnoffDen1,
  "bật đèn thứ 2": turnonDen2,
  "tắt đèn thứ 2": turnoffDen2,
  "bật đèn thứ 3": turnonDen3,
  "tắt đèn thứ 3": turnoffDen3,
  "bật đèn thứ 4": turnonDen4,
  "tắt đèn thứ 4": turnoffDen4,
  "mở rèm thứ nhất": turnonRem1,
  "kéo rèm thứ nhất": turnoffRem1,
  "mở rèm thứ 2": turnonRem2,
  "kéo rèm thứ 2": turnoffRem2,
  "bật tất cả": turnonDen,
  "tắt tất cả": turnoffDen,
};

function startListening() {
  recognition = new webkitSpeechRecognition();
  recognition.lang = "vi-VN";
  recognition.onresult = function (event) {
    const result = event.results[0][0].transcript.toLowerCase();
    console.log("You said: " + result);
    for (const command in voiceCommands) {
      if (result.includes(command)) {
        voiceCommands[command]();
      }
    }
  };
  recognition.onerror = function (event) {
    console.error("Speech recognition error: " + event.error);
  };
  recognition.onend = function () {
    recognition.start();
  };
  recognition.start();
}
