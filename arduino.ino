const int MINI_PAUSA = 100;
const int MAXI_PAUSA = 5 * MINI_PAUSA;

const int NUM_TOT_PIN_ARDUINO = 13 + 1;
const int NUM_COMBINAZIONI = 9 + 1;
const int NUM_SEGMENTI = 7;

const bool numeroCombinazioni[NUM_COMBINAZIONI][NUM_SEGMENTI] = {
// A      B      C      D      E      F      G
  {true , true , true , true , true , true , false},  // 0
  {false, true , true , false, false, false, false},  // 1
  {true , true , false, true , true , false, true },  // 2
  {true , true , true , true , false, false, true },  // 3
  {false, true , true , false, false, true , true },  // 4
  {true , false, true , true , false, true , true },  // 5
  {true , false, true , true , true , true , true },  // 6
  {true , true , true , false, false, false, false},  // 7
  {true , true , true , true , true , true , true },  // 8
  {true , true , true , true , false, true , true },  // 9
};

class ArduinoPinComponente {
  protected:
    int pin;
  public:
    static bool pinDisponibili[NUM_TOT_PIN_ARDUINO];
    
    ArduinoPinComponente() {
      pin = 0;
      while(pinDisponibili[pin]) { pin++; };
      pinDisponibili[pin] = true; 
      pinMode(pin, OUTPUT);
    }

    void accendi() { digitalWrite(pin, HIGH); };
    void spegni()  { digitalWrite(pin, LOW ); };
};

bool ArduinoPinComponente::pinDisponibili[NUM_TOT_PIN_ARDUINO] = { true, true, false, false, false, false, false, false, false, false, false, false, false, false };

class Segmento : public ArduinoPinComponente {};

class Display {
  private:
  	Segmento **segmentoArr;
    int size = NUM_SEGMENTI;
  public:
    Display(){
      segmentoArr = new Segmento*[size];
      for(int i = 0; i < size; i++) {
        segmentoArr[i] = new Segmento();
      };
    };
    
    void reset() {
      for (int i = 0; i < size; i++) {
        segmentoArr[i]->spegni();
      };
    };

    void scriviNumero(int numero) {
      reset();
      for (int i = 0; i < size; i++) {
        if(numeroCombinazioni[numero][i]) {
          segmentoArr[i]->accendi();
        }
      };
    };
};

Display primoDisplay;

void loop() {
  for (int i = 0; i < NUM_COMBINAZIONI; i++) {
    primoDisplay.scriviNumero(i);
    delay(MAXI_PAUSA);
  };
};

void setup() {}
