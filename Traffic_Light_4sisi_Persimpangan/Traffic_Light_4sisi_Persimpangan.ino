//Definisi Pin Sisi UTARA (North) 
const int NORTH_RED    = 2;
const int NORTH_YELLOW = 3;
const int NORTH_GREEN  = 4;
//Definisi Pin Sisi SELATAN (South) 
const int SOUTH_RED    = 5;
const int SOUTH_YELLOW = 6;
const int SOUTH_GREEN  = 7;
//Definisi Pin Sisi TIMUR (East) 
const int EAST_RED     = 8;
const int EAST_YELLOW  = 9;
const int EAST_GREEN   = 10;
//Definisi Pin Sisi BARAT (West) 
const int WEST_RED     = 11;
const int WEST_YELLOW  = 12;
const int WEST_GREEN   = 13;
//Durasi Waktu (milidetik) 
const int GREEN_TIME         = 5000; // Hijau: 5 detik
const int YELLOW_BLINK_TOTAL = 2000; // Total durasi fase kuning berkedip: 2 detik
const int YELLOW_BLINK_ON    = 400;  // Kuning menyala selama 400 ms per kedip
const int YELLOW_BLINK_OFF   = 300;  // Kuning mati selama 300 ms per kedip
void allOff(int red, int yellow, int green) {
  digitalWrite(red,    LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green,  LOW);
}
void setRed(int red, int yellow, int green) {
  digitalWrite(red,    HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green,  LOW);
}
void setGreen(int red, int yellow, int green) {
  digitalWrite(red,    LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green,  HIGH);
}
void blinkYellow(int red, int yellow, int green) {
  int elapsed = 0;
  allOff(red, yellow, green); 
  while (elapsed < YELLOW_BLINK_TOTAL) {
    // Nyalakan kuning
    digitalWrite(red,    LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(green,  LOW);
    delay(YELLOW_BLINK_ON);
    elapsed += YELLOW_BLINK_ON;
    // Matikan kuning (jeda gelap)
    digitalWrite(yellow, LOW);
    delay(YELLOW_BLINK_OFF);
    elapsed += YELLOW_BLINK_OFF;
  }
  // Pastikan kuning benar-benar mati setelah selesai
  digitalWrite(yellow, LOW);
}
void runPhase(
  int activeRed, int activeYellow, int activeGreen,       
  int parallelRed, int parallelYellow, int parallelGreen, 
  int cross1Red, int cross1Yellow, int cross1Green,       
  int cross2Red, int cross2Yellow, int cross2Green       
) {
  //Fase HIJAU
  setGreen(activeRed, activeYellow, activeGreen);
  setRed(parallelRed, parallelYellow, parallelGreen);
  setRed(cross1Red, cross1Yellow, cross1Green);
  setRed(cross2Red, cross2Yellow, cross2Green);
  delay(GREEN_TIME);
  //Fase KUNING BERKEDIP (transisi)
  blinkYellow(activeRed, activeYellow, activeGreen);
  // Tiga sisi lain tetap merah (tidak berubah)
  //Fase MERAH: sisi aktif kini merah
  setRed(activeRed, activeYellow, activeGreen);
  delay(500); // Jeda 0.5 detik sebelum fase berikutnya
}

void setup() {
  // Inisialisasi pin sisi Utara
  pinMode(NORTH_RED,    OUTPUT);
  pinMode(NORTH_YELLOW, OUTPUT);
  pinMode(NORTH_GREEN,  OUTPUT);
  // Inisialisasi pin sisi Selatan
  pinMode(SOUTH_RED,    OUTPUT);
  pinMode(SOUTH_YELLOW, OUTPUT);
  pinMode(SOUTH_GREEN,  OUTPUT);
  // Inisialisasi pin sisi Timur
  pinMode(EAST_RED,     OUTPUT);
  pinMode(EAST_YELLOW,  OUTPUT);
  pinMode(EAST_GREEN,   OUTPUT);
  // Inisialisasi pin sisi Barat
  pinMode(WEST_RED,     OUTPUT);
  pinMode(WEST_YELLOW,  OUTPUT);
  pinMode(WEST_GREEN,   OUTPUT);
  // Kondisi awal: semua merah (kondisi aman saat inisialisasi)
  setRed(NORTH_RED, NORTH_YELLOW, NORTH_GREEN);
  setRed(SOUTH_RED, SOUTH_YELLOW, SOUTH_GREEN);
  setRed(EAST_RED,  EAST_YELLOW,  EAST_GREEN);
  setRed(WEST_RED,  WEST_YELLOW,  WEST_GREEN);
  delay(1000);
}

void loop() {
  //FASE 1: UTARA HIJAU -> KUNING BERKEDIP -> MERAH
  runPhase(
    NORTH_RED, NORTH_YELLOW, NORTH_GREEN,
    SOUTH_RED, SOUTH_YELLOW, SOUTH_GREEN,
    EAST_RED,  EAST_YELLOW,  EAST_GREEN,
    WEST_RED,  WEST_YELLOW,  WEST_GREEN
  );
  //FASE 2: TIMUR HIJAU -> KUNING BERKEDIP -> MERAH 
  runPhase(
    EAST_RED,  EAST_YELLOW,  EAST_GREEN,
    WEST_RED,  WEST_YELLOW,  WEST_GREEN,
    NORTH_RED, NORTH_YELLOW, NORTH_GREEN,
    SOUTH_RED, SOUTH_YELLOW, SOUTH_GREEN
  );
  //FASE 3: SELATAN HIJAU -> KUNING BERKEDIP -> MERAH
  runPhase(
    SOUTH_RED, SOUTH_YELLOW, SOUTH_GREEN,
    NORTH_RED, NORTH_YELLOW, NORTH_GREEN,
    EAST_RED,  EAST_YELLOW,  EAST_GREEN,
    WEST_RED,  WEST_YELLOW,  WEST_GREEN
  );
  //FASE 4: BARAT HIJAU -> KUNING BERKEDIP -> MERAH
  runPhase(
    WEST_RED,  WEST_YELLOW,  WEST_GREEN,
    EAST_RED,  EAST_YELLOW,  EAST_GREEN,
    NORTH_RED, NORTH_YELLOW, NORTH_GREEN,
    SOUTH_RED, SOUTH_YELLOW, SOUTH_GREEN
  );
}
