/** DELETE ALL FILES ON SPIFFS **/


#include <TFT_eSPI.h>       // Include the graphics library
#include <SPIFFS.h>          // Include the SPIFFS library
#include <FS.h>              // Include the File System library

TFT_eSPI tft = TFT_eSPI();  // Create an instance of the display library

void setup() {
  Serial.begin(115200);
  tft.begin();              // Initialize the TFT display
  tft.setRotation(1);       // Set the rotation of the display
  tft.fillScreen(TFT_BLACK); // Clear the screen with black

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  Serial.println("SPIFFS mounted successfully");

  // List and delete all files in the root directory
  deleteAllFiles();
}

void loop() {
  // Put your main code here, to run repeatedly:
  delay(1000); // Adjust the delay as needed
}

void deleteAllFiles() {
  fs::File root = SPIFFS.open("/");
  fs::File file = root.openNextFile();

  while(file){
    Serial.print("Deleting File: ");
    Serial.println(file.name());

    if (SPIFFS.remove(file.name())) {
      Serial.println("File deleted successfully");
    } else {
      Serial.println("File deletion failed");
    }

    file = root.openNextFile(); // Move to the next file in the directory
  }
}
