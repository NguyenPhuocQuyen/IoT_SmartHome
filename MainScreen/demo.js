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

// For two light
function toggleButtonClick(numlight) {
  var Led1Status = document.getElementById("toggle" + numlight).checked;
  var firebaseRef = firebase
    .database()
    .ref()
    .child("Led")
    .child("Led" + numlight + "Status");
  var slider = document.getElementById("slider" + numlight);
  var output = document.getElementById("slider-value" + numlight);

  if (Led1Status == true) {
    // post to firebase
    // firebaseRef.set("100");
    firebaseRef.set(parseInt("255"));
    slider.value = 255;
    output.innerHTML = "Light " + numlight + ": " + slider.value;
  } else {
    // firebaseRef.set("0");
    firebaseRef.set(parseInt("0"));
    slider.value = 0;
    output.innerHTML = "Light " + numlight + ": " + slider.value;
  }
}
// Light 1
document.addEventListener("DOMContentLoaded", function () {
  var slider = document.getElementById("slider1");
  var output = document.getElementById("slider-value1");

  output.innerHTML = slider.value;

  slider.oninput = function () {
    output.innerHTML = "Light 1: " + this.value;
    var sliderValue = parseInt(this.value);

    var firebaseRef = firebase
      .database()
      .ref()
      .child("Led")
      .child("Led1Status");
    firebaseRef.set(sliderValue); // Gửi giá trị đến Firebase
  };
});
// Light 2
document.addEventListener("DOMContentLoaded", function () {
  var slider1 = document.getElementById("slider2");
  var output1 = document.getElementById("slider-value2");

  output1.innerHTML = slider1.value;

  slider1.oninput = function () {
    output1.innerHTML = "Light 2: " + this.value;
    var sliderValue1 = parseInt(this.value);

    var firebaseRef = firebase
      .database()
      .ref()
      .child("Led")
      .child("Led2Status");
    firebaseRef.set(sliderValue1); // Gửi giá trị đến Firebase
  };
});

// // Quạt
// function toggleButtonClickFan(numspan) {
//   var Span1Status = document.getElementById("toggleFan" + numspan).checked;
//   var firebaseRef = firebase
//     .database()
//     .ref()
//     .child("Span")
//     .child("Span" + numspan + "Status");

//   if (Span1Status == true) {
//     // post to firebase
//     // firebaseRef.set("1");
//     firebaseRef.set(parseInt("0"));
//   } else {
//     // firebaseRef.set("0");
//     firebaseRef.set(parseInt("1"));
//   }
// }
function toggleButtonClickFan(numspan) {
  var Span1Status = document.getElementById("toggleFan" + numspan).checked;
  var firebaseURL = "https://iotsmarthome-e9c19-default-rtdb.firebaseio.com/Span/Span" + numspan + "Status.json";

  var xhr = new XMLHttpRequest();
  xhr.open("PUT", firebaseURL);
  xhr.setRequestHeader("Content-Type", "application/json");

  if (Span1Status) {
    xhr.send(JSON.stringify(1)); // Gửi giá trị 1 khi nút được kích hoạt
  } else {
    xhr.send(JSON.stringify(0)); // Gửi giá trị 0 khi nút không được kích hoạt
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
    firebaseRef.set(parseInt("1"));
  } else {
    firebaseRef.set(parseInt("0"));
  }
}

// // Cửa
function toggleButtonClickCua(numcua) {
  var Cua1Status = document.getElementById("toggleCua" + numcua).checked;
  var firebaseRef = firebase
    .database()
    .ref()
    .child("Cua")
    .child("Cua" + numcua + "Status");

  if (Cua1Status == true) {
    // post to firebase
    firebaseRef.set(parseInt("1"));
    setTimeout(function() {
      firebaseRef.set(parseInt("2"));
    }, 4000);
  } else {
    firebaseRef.set(parseInt("0"));
    setTimeout(function() {
      firebaseRef.set(parseInt("2"));
    }, 4000);
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

document.addEventListener("DOMContentLoaded", async () => {
  const video1 = document.getElementById("cameraFeed"); // Webcam máy tính
  const video2 = document.getElementById("cameraFeed1"); // Camera từ AndroidCam

  try {
    const devices = await navigator.mediaDevices.enumerateDevices();
    const videoInputs = devices.filter(
      (device) => device.kind === "videoinput"
    );

    if (videoInputs.length >= 2) {
      // Giả sử rằng camera máy tính là thiết bị đầu tiên và AndroidCam là thiết bị thứ hai
      const stream1 = await navigator.mediaDevices.getUserMedia({
        video: { deviceId: videoInputs[0].deviceId },
      });
      video1.srcObject = stream1;

      const stream2 = await navigator.mediaDevices.getUserMedia({
        video: { deviceId: videoInputs[1].deviceId },
      });
      video2.srcObject = stream2;
    } else {
      console.error("Không tìm thấy đủ camera.");
    }
  } catch (error) {
    console.error("Error accessing the camera: ", error);
  }
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
  // firebaseRef.set("1")
  firebaseRef.set(parseInt("0"));
}
function turnoffFan() {
  var firebaseRef = firebase
    .database()
    .ref()
    .child("Span")
    .child("Span1Status");
  // firebaseRef.set("0")
  firebaseRef.set(parseInt("1"));
}
//Hàm gọi của cửa
function turnonCua() {
  var firebaseRef = firebase.database().ref().child("Cua").child("Cua1Status");
  firebaseRef.set(parseInt("1"));
}
function turnoffCua() {
  var firebaseRef = firebase.database().ref().child("Cua").child("Cua1Status");
  firebaseRef.set(parseInt("0"));
}
//Hàm gọi của đèn
function turnonDen() {
  var firebaseRef0 = firebase.database().ref().child("Led").child("Led1Status");
  var firebaseRef1 = firebase.database().ref().child("Led").child("Led2Status");
  var firebaseRef2 = firebase.database().ref().child("Led").child("Led3Status");
  var firebaseRef3 = firebase.database().ref().child("Led").child("Led4Status");
  firebaseRef0.set(parseInt("255"));
  firebaseRef1.set(parseInt("255"));
  firebaseRef2.set(parseInt("255"));
  firebaseRef3.set(parseInt("255"));
}
function turnoffDen() {
  var firebaseRef0 = firebase.database().ref().child("Led").child("Led1Status");
  var firebaseRef1 = firebase.database().ref().child("Led").child("Led2Status");
  var firebaseRef2 = firebase.database().ref().child("Led").child("Led3Status");
  var firebaseRef3 = firebase.database().ref().child("Led").child("Led4Status");
  firebaseRef0.set(parseInt("0"));
  firebaseRef1.set(parseInt("0"));
  firebaseRef2.set(parseInt("0"));
  firebaseRef3.set(parseInt("0"));
}
function turnonDen1() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led1Status");
  firebaseRef.set(parseInt("255"));
}
function turnoffDen1() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led1Status");
  firebaseRef.set(parseInt("0"));
}
function turnonDen2() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led2Status");
  firebaseRef.set(parseInt("255"));
}
function turnoffDen2() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led2Status");
  firebaseRef.set(parseInt("0"));
}
function turnonDen3() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led3Status");
  firebaseRef.set(parseInt("1"));
}
function turnoffDen3() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led3Status");
  firebaseRef.set(parseInt("0"));
}
function turnonDen4() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led4Status");
  firebaseRef.set(parseInt("1"));
}
function turnoffDen4() {
  var firebaseRef = firebase.database().ref().child("Led").child("Led1Status");
  firebaseRef.set(parseInt("0"));
}

//Hàm gọi của rèm
function turnonRem1() {
  var firebaseRef = firebase.database().ref().child("Rem").child("Rem1Status");
  firebaseRef.set(parseInt("1"));
}
function turnoffRem1() {
  var firebaseRef = firebase.database().ref().child("Rem").child("Rem1Status");
  firebaseRef.set(parseInt("0"));
}
function turnonRem2() {
  var firebaseRef = firebase.database().ref().child("Rem").child("Rem2Status");
  firebaseRef.set(parseInt("1"));
}
function turnoffRem2() {
  var firebaseRef = firebase.database().ref().child("Rem").child("Rem2Status");
  firebaseRef.set(parseInt("0"));
}

//Hàm nhận diện giọng nói
let recognition;

const voiceCommands = {
  "đăng xuất": logout_function,
  "linh": inforlinh,
  "thuỳ": inforthuy,
  "phú": inforphu,
  "quyền": inforquyen,
  "anh": inforanh,
  "thành": inforthanh,
  "mở quạt": turnonFan,
  "tắt quạt": turnoffFan,
  "mở cửa": turnonCua,
  "đóng cửa": turnoffCua,
  "mở đèn một.": turnonDen1,
  "tắt đèn một": turnoffDen1,
  "mở đèn 2": turnonDen2,
  "tắt đèn 2": turnoffDen2,
  "bật đèn 3": turnonDen3,
  "tắt đèn 3": turnoffDen3,
  "bật đèn 4": turnonDen4,
  "tắt đèn 4": turnoffDen4,
  "mở rèm": turnonRem1,
  "kéo rèm": turnoffRem1,
  "mở rèm 2": turnonRem2,
  "kéo rèm 2": turnoffRem2,
  "tất cả đèn": turnonDen,
  "tắt tất cả": turnoffDen,
};

let isListening = false;

function startListening() {
  if (isListening) {
    return; // Nếu đã đang lắng nghe, không khởi động lại
  }
  // document.getElementById("listeningStatus").innerHTML = "Đang lắng nghe...";
  recognition = new webkitSpeechRecognition();
  recognition.lang = "vi-VN";
  recognition.continuous = true; // Thiết lập này cho phép nhận dạng liên tục
  recognition.interimResults = true; // Có thể thấy kết quả tạm thời (chưa chắc chắn)

  recognition.onresult = function (event) {
    document.getElementById("listeningStatus").innerHTML = ""; // Xóa trạng thái khi có kết quả
    const result = event.results[event.resultIndex][0].transcript.toLowerCase();
    console.log("You said: " + result);
    for (const command in voiceCommands) {
      if (result.includes(command)) {
        voiceCommands[command]();
        break; // Thực hiện lệnh đầu tiên tìm thấy và dừng vòng lặp
      }
    }
  };

  recognition.onerror = function (event) {
    document.getElementById("listeningStatus").innerHTML = ""; // Xóa trạng thái khi có lỗi
    console.error("Speech recognition error: " + event.error);
  };

  recognition.onend = function () {
    document.getElementById("listeningStatus").innerHTML = "";
    if (isListening) {
      recognition.start(); // Chỉ khởi động lại nếu người dùng vẫn muốn lắng nghe
    }
  };

  recognition.start();
  isListening = true; // Cập nhật trạng thái lắng nghe
}

function stopListening() {
  if (recognition) {
    recognition.stop(); // Dừng nhận dạng giọng nói
  }
  isListening = false; // Cập nhật trạng thái không lắng nghe
  document.getElementById("listeningStatus").innerHTML = ""; // Xóa trạng thái
}

function ChangePasswordDoor() {
  event.preventDefault();
  window.location.href = "../PasswordDoor/passDoor.html";
}
