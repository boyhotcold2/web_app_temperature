#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>//thư viện Firebase
#include <dht_nonblocking.h>//thư viện DHT11

#define DHT_SENSOR_TYPE DHT_TYPE_11  //loại cảm biến đang sử dụng,DHT11

#define WIFI_SSID "BiBu" // tên wifi
#define WIFI_PASSWORD "14101966" //pass wifi
#define FIREBASE_HOST "https://smart-city-html-default-rtdb.firebaseio.com/"   //link đến realtime database của firebase
#define FIREBASE_AUTH "KwUaUBRre2pn1WAdIzWKOCq5RKtGmVylNjWiwELL"                  //mã authentication của database

FirebaseData HCMDATA;
FirebaseData HNDATA; 
FirebaseData DLDATA; //khai báo database
FirebaseJson json;    

static const int DHT_SENSOR_PIN = D7;  //khai báo chân đọc data từ DHT11
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE ); //khởi tạo hàm đọc cảm biến từ thư viện
struct HCM{
    float co2=90;//khai báo biến lưu giá trị chất lượng không khí
    float gio=100;//khai báo biến lưu giá trị lượng mưa
    float uv=10;//khai báo biến lưu giá trị mật độ uv
    float noise=85;//khai báo biến lưu giá trị độ ồn
    float temperature;//khai báo biến lưu giá trị nhiệt độ
    float humidity;   // khai báo biến lưu giá trị độ ẩm
};

    struct DALAT{
    float co2=60;//khai báo biến lưu giá trị chất lượng không khí
    float gio=80;//khai báo biến lưu giá trị lượng mưa
    float uv=8;//khai báo biến lưu giá trị mật độ uv
    float noise=100;//khai báo biến lưu giá trị độ ồn
    float temperature;//khai báo biến lưu giá trị nhiệt độ
    float humidity;   // khai báo biến lưu giá trị độ ẩm
};

    struct HANOI{
    float co2=100;//khai báo biến lưu giá trị chất lượng không khí
    float gio=70;//khai báo biến lưu giá trị lượng mưa
    float uv=6;//khai báo biến lưu giá trị mật độ uv
    float noise=90;//khai báo biến lưu giá trị độ ồn
    float temperature;//khai báo biến lưu giá trị nhiệt độ
    float humidity;   // khai báo biến lưu giá trị độ ẩm
};
void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  //cài đặt thời gian đọc timeout 
  Firebase.setReadTimeout(HCMDATA, 1000 * 60);
  Firebase.setReadTimeout(DLDATA, 1000 * 60);
  Firebase.setReadTimeout(HNDATA, 1000 * 60);
  //size ghi limit
  //tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(HCMDATA, "tiny");
  Firebase.setwriteSizeLimit(DLDATA, "tiny");
  Firebase.setwriteSizeLimit(HNDATA, "tiny");
  Serial.println("------------------------------------");
  Serial.println("Connected...");
}
//hàm đọc giá trị cảm biến trả về
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );
  if( millis( ) - measurement_timestamp > 1000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }
  return( false );
}   
void loop()
{   
  HCM hcm; //khai báo biến cấu trúc chứa dữ liệu của thành phố Hồ Chí Minh
  DALAT dl; //khai báo biến cấu trúc chứa dữ liệu của Thành phố Đà Lạt
  HANOI hn; //khai báo biến cấu trúc chứa dữ liệu của Thành phố Hà Nội
  float temperature;//khai báo biến lưu giá trị nhiệt độ
  float humidity;   // khai báo biến lưu giá trị độ ẩm

  if( measure_environment( &temperature, &humidity ) == true ) //hàm đọc giá trị trả về là true thì lưu các giá trị vào các biến đã khởi tạo
  {
    hcm.temperature=dl.temperature=hn.temperature = temperature;
    hcm.humidity=dl.humidity=hn.humidity = humidity;
    
    int datahcm[6],datadl[6],datahn[6]; //khai báo mảng chứa dữ liệu của các thành phố
    
    //dữ liệu thời tiết của thành phố Hồ Chí Minh
    datahcm[0]=hcm.temperature;//lưu vào data0
    datahcm[1]=hcm.humidity;//lưu vào data1
    datahcm[2]=hcm.co2;//lưu vào data2
    datahcm[3]=hcm.gio;//lưu vào data3
    datahcm[4]=hcm.uv;//lưu vào data4
    datahcm[5]=hcm.noise;//lưu vào data5

    //dữ liệu thời tiết của thành phố Đà Lạt
    datadl[0]=dl.temperature;//lưu vào data0
    datadl[1]=dl.humidity;//lưu vào data1
    datadl[2]=dl.co2;//lưu vào data2
    datadl[3]=dl.gio;//lưu vào data3
    datadl[4]=dl.uv;//lưu vào data4
    datadl[5]=dl.noise;//lưu vào data5

    datahn[0]=hn.temperature;//lưu vào data0
    datahn[1]=hn.humidity;//lưu vào data1
    datahn[2]=hn.co2;//lưu vào data2
    datahn[3]=hn.gio;//lưu vào data3
    datahn[4]=hn.uv;//lưu vào data4
    datahn[5]=hn.noise;//lưu vào data5
    ///--------------------------------------------------////
    json.set("/TEMP", datahcm[0]);//set value TEMP với key là datahcm[0]
    json.set("/HUMI", datahcm[1]);//set value HUMI với key là datahcm[1]
    json.set("/CO2",  datahcm[2]);//set value AQI với key là datahcm[2]
    json.set("/GIO", datahcm[3]);//set value RAIN với key là datahcm[3]
    json.set("/UV",   datahcm[4]);//set value UV với key là datahcm[4]
    json.set("/NOISE",datahcm[5]);//set value NOISE với key là datahcm[5]
    Firebase.updateNode(HCMDATA,"/HCM",json);//up data lên node có tên là HCM

    json.set("/TEMP", datadl[0]);//set value TEMP với key là datadl[0]
    json.set("/HUMI", datadl[1]);//set value HUMI với key là datadl[1]
    json.set("/CO2",  datadl[2]);//set value AQI với key là datadl[2]
    json.set("/GIO", datadl[3]);//set value RAIN với key là datadl[3]
    json.set("/UV",   datadl[4]);//set value UV với key là datadl[4]
    json.set("/NOISE",datadl[5]);//set value NOISE với key là datadl[5]
    Firebase.updateNode(DLDATA,"/DALAT",json);//up data lên node có tên là DL

    json.set("/TEMP", datahn[0]);//set value TEMP với key là datahcm[0]
    json.set("/HUMI", datahn[1]);//set value HUMI với key là datahcm[1]
    json.set("/CO2",  datahn[2]);//set value AQI với key là datahcm[2]
    json.set("/GIO", datahn[3]);//set value RAIN với key là datahcm[3]
    json.set("/UV",   datahn[4]);//set value UV với key là datahcm[4]
    json.set("/NOISE",datahn[5]);//set value NOISE với key là datahcm[5]
    Firebase.updateNode(HNDATA,"/HANOI",json);//up data lên node có tên là HN
    Serial.println( "---------------------------Dữ liệu của Thành Phố Hồ Chí Minh-------------------------" );
    Serial.print( "Temperature = " );
    Serial.print( hcm.temperature, 1 );
    Serial.print( " *C, Humidity = " );
    Serial.print( hcm.humidity, 1 );
    Serial.println( "%" );
    Serial.print( "UV = " );
    Serial.print( hcm.uv, 1 );
    Serial.print( ", NOISE = " );
    Serial.print( hcm.noise, 1 );
    Serial.println( "dB" );
    Serial.print( "CO2 = " );
    Serial.print( hcm.co2, 1 );
    Serial.print( " co2, GIO = " );
    Serial.print( hcm.gio, 1 );
    Serial.println( "km/h" );
    Serial.println( "-------------------------------------------------------------------------------------" );

     Serial.println( "---------------------------Dữ liệu của Thành Phố Đà Lạt-------------------------" );
    Serial.print( "Temperature = " );
    Serial.print( dl.temperature, 1 );
    Serial.print( " *C, Humidity = " );
    Serial.print( dl.humidity, 1 );
    Serial.println( "%" );
    Serial.print( "UV = " );
    Serial.print( dl.uv, 1 );
    Serial.print( ", NOISE = " );
    Serial.print( dl.noise, 1 );
    Serial.println( "dB" );
    Serial.print( "CO2 = " );
    Serial.print( dl.co2, 1 );
    Serial.print( " co2, GIO = " );
    Serial.print( dl.gio, 1 );
    Serial.println( "km/h" );
    Serial.println( "-------------------------------------------------------------------------------------" );

     Serial.println( "---------------------------Dữ liệu của Thành Phố Hà Nội-------------------------" );
    Serial.print( "Temperature = " );
    Serial.print( hn.temperature, 1 );
    Serial.print( " *C, Humidity = " );
    Serial.print( hn.humidity, 1 );
    Serial.println( "%" );
    Serial.print( "UV = " );
    Serial.print( hn.uv, 1 );
    Serial.print( ", NOISE = " );
    Serial.print( hn.noise, 1 );
    Serial.println( "dB" );
    Serial.print( "CO2 = " );
    Serial.print( hn.co2, 1 );
    Serial.print( " co2, GIO = " );
    Serial.print( hn.gio, 1 );
    Serial.println( "km/h" );
    Serial.println( "-------------------------------------------------------------------------------------" );
  }
}
