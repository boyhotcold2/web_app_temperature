window.onload = function onLoad() {  
    var firebaseConfig = {
        apiKey: "AIzaSyCwg7NKmk2zeCd0jHQ-ON34x4DTpQdLMy8",
        authDomain: "smart-city-html.firebaseapp.com",
        databaseURL: "https://smart-city-html-default-rtdb.firebaseio.com",
        projectId: "smart-city-html",
        storageBucket: "smart-city-html.appspot.com",
        messagingSenderId: "416162317122",
        appId: "1:416162317122:web:8595d3e0c9daf8ad12bedb"
    };
    // Initialize Firebase
    firebase.initializeApp(firebaseConfig);
    firebase.analytics();

    //functions
    var nhietDo = document.getElementById('nhietdo');
    var doAm = document.getElementById('doam');
    var Uv = document.getElementById('uv');
    var nongdoco2 = document.getElementById('co2');
    var aNoise = document.getElementById('noise');
    var winD = document.getElementById('wind');

    var dbRef = firebase.database().ref().child('DALAT/TEMP');
    var dbRef2 = firebase.database().ref().child('DALAT/HUMI');
    var dbRef3 = firebase.database().ref().child('DALAT/UV');
    var dbRef4 = firebase.database().ref().child('DALAT/CO2');
    var dbRef5 = firebase.database().ref().child('DALAT/NOISE');
    var dbRef6 = firebase.database().ref().child('DALAT/GIO');


    dbRef.on('value', snap => nhietDo.innerText = snap.val()+" °C");
    dbRef2.on('value', snap => doAm.innerText = snap.val()+" %");
    dbRef3.on('value', snap => Uv.innerText = snap.val()+" UV");
    dbRef4.on('value', snap => nongdoco2.innerText = snap.val()+" PPM");
    dbRef5.on('value', snap => aNoise.innerText = snap.val()+" dB");
    dbRef6.on('value', snap => winD.innerText = snap.val()+" km/h");
}
