# include <iostream>
# include <string>
# include <fstream>
# include <windows.h>

using namespace std ;

void printAll_Headphone_Device() ;
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

void printAll_Headphone_Device() {
    // 取得系統中的音訊輸出裝置數量
    UINT deviceCount = waveOutGetNumDevs();

    if (deviceCount == 0) cout << "No audio output devices found." << endl;

    // 迭代每個音訊輸出裝置，並取得其資訊
    for (UINT deviceId = 0; deviceId < deviceCount; ++deviceId) {
        /*
        你可以在 waveOutCaps 中找到其他音訊裝置的資訊
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

        // function
        // convert TCHAR[32](waveOutCaps.szPname) to string
        wstring wideStr( waveOutCaps.szPname ) ;
        string narrowStr( wideStr.begin(), wideStr.end() ) ;

        // if "Headphones" in device name : print
        if ( result == MMSYSERR_NOERROR ) cout << waveOutCaps.szPname << endl ;
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
        printAll_Headphone_Device() ;
        cout << endl << "headphone device name : " ;
        cin >> device_name ;
        cout << "music file path : " ;
        cin >> audio_filePath ;
        init_setting << device_name << "\n" << audio_filePath << "\n" ;
        init_setting.close() ;
    }
}

string getCurrent_Device() {
    ;
}

void playAlertSound( const string filePath ) {
    ;
}

void popupWindow() {
    ;
}