# include <iostream>
# include <string>
# include <fstream>
# include <windows.h>
# include <tchar.h>

using namespace std ;

void printAll_Device() ;
void load_setfile( string & device_name, string & audio_filePath ) ;
string getCurrent_Device() ;
void playAlertSound( const string filePath ) ;
void popupWindow() ;

int main() {
    string headphone_name, audio_filePath, device_name ;
    load_setfile( headphone_name, audio_filePath ) ;

    while(true) {
        device_name = getCurrent_Device() ;
        if ( device_name != headphone_name ) {
            playAlertSound( audio_filePath ) ;
            popupWindow() ;
        }

        //std::this_thread::sleep_for(std::chrono::minutes(1));
    }
}

void printAll_Device() {
    UINT deviceCount = waveOutGetNumDevs(); // 取得系統中的音訊輸出裝置數量

    if (deviceCount == 0) cout << "No audio output devices found." << endl;

    // 迭代每個音訊輸出裝置，並取得其資訊
    for (UINT deviceId = 0; deviceId < deviceCount; ++deviceId) {
        /*
        waveOutCaps資訊結構
        typedef struct {
            WORD    wMid;
            WORD    wPid;
            MMVERSION vDriverVersion;
            TCHAR   szPname[MAXPNAMELEN];
            DWORD   dwFormats;
            WORD    wChannels;
            WORD    wReserved1;
            DWORD   dwSupport;
        }
        */

        WAVEOUTCAPS waveOutCaps;
        MMRESULT result = waveOutGetDevCaps(deviceId, &waveOutCaps, sizeof(WAVEOUTCAPS));

        if ( result == MMSYSERR_NOERROR ) {
            cout << waveOutCaps.szPname << endl ;
        }

        else cerr << "Error getting device information for device " << deviceId << endl;
    }
}

void load_setfile( string & device_name, string & audio_filePath ) {
    ifstream load("setting.txt") ;

    if ( load.is_open() ) {
        getline( load, device_name ) ;
        getline( load, audio_filePath ) ;
        load.close() ;
    }
    
    else {
        load.close() ;
        ofstream init_setting("setting.txt") ;

        cout << "All headphone device : " ;
        printAll_Device() ;

        cout << endl << "headphone device name : " ;
        std::getline( cin, device_name ) ;
        
        cout << "music file path : " ;
        std::getline( cin, audio_filePath ) ;

        init_setting << device_name << "\n" << audio_filePath << "\n" ;
        init_setting.close() ;
    }
}

string getCurrent_Device() {
    WAVEOUTCAPS waveOutCaps ;
    MMRESULT result = waveOutGetDevCaps(WAVE_MAPPER, &waveOutCaps, sizeof(WAVEOUTCAPS));

    if ( result == MMSYSERR_NOERROR ) {
        std::string device_name( waveOutCaps.szPname ) ;
        return device_name ;
    }
    else cerr << "Error getting current device information" << endl ;
}

void playAlertSound( const string filePath ) {
    ;
}

void popupWindow() {
    ;
}