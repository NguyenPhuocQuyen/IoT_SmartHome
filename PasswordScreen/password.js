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
function changePassword() {
  var oldPassword = document.getElementById("password-old").value;
  var newPassword = document.getElementById("password-new").value;

  var userRef = firebase.database().ref("PasswordWeb");
  userRef
    .once("value")
    .then(function (snapshot) {
      var userData = snapshot.val();
      if (userData.password === oldPassword) {
        return userRef.update({ password: newPassword });
      } else {
        throw new Error("Incorrect current password!");
      }
    })
    .then(function () {
      alert("Password changed successfully!");
      window.location.href = "../LoginScreen/login.html";
    })
    .catch(function (error) {
      alert(error.message);
    });
}

function Back() {
  window.location.href = "../LoginScreen/login.html";
}
