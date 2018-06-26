import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { BluetoothSerial } from '@ionic-native/bluetooth-serial';
import { AlertController } from 'ionic-angular';

@Component({
  selector: 'page-connection',
  templateUrl: 'connection.html'
})

export class ConnectionPage {
  

  unpairedDevices: any;
  pairedDevices: any;
  gettingDevices: Boolean;
  constructor(public navCtrl: NavController, private bluetoothSerial: BluetoothSerial, private alertCtrl: AlertController) {
        bluetoothSerial.enable();
        
  }
    
  


  isenabled: boolean;
  success = (data) => alert("Accoppiamento eseguito");
  fail = (error) => alert(error);


  disconnect() {
    let alert = this.alertCtrl.create({
      title: 'Disconnect?',
      message: 'Do you want to Disconnect?',
      buttons: [
        {
          text: 'Cancel',
          role: 'cancel',
          handler: () => {
            console.log('Cancel clicked');
          }
        },
        {
          text: 'Disconnect',
          handler: () => {
            this.bluetoothSerial.disconnect();
          }
        }
      ]
    });
    alert.present();
  }

pairSmartShoes() {
    let alert = this.alertCtrl.create({
      title: 'Connect',
      message: 'Do you want to connect with?',
      buttons: [
        {
          text: 'Cancel',
          role: 'cancel',
          handler: () => {
            console.log('Cancel clicked');
          }
        },
        {
          text: 'Connect',
          handler: () => {
            this.bluetoothSerial.connect('28:16:AD:63:E6:5A').subscribe(this.success, this.fail);

          }
        }
      ]
    });
    alert.present();

  }
  
  

startScanning() {
    this.pairedDevices = null;
    this.unpairedDevices = null;
    this.gettingDevices = true;
    this.bluetoothSerial.discoverUnpaired().then((success) => {
      this.unpairedDevices = success;
      this.gettingDevices = false;
      success.forEach(element => {
        // alert(element.name);
      });
    },
      (err) => {
        console.log(err);
      })

    this.bluetoothSerial.list().then((success) => {
      this.pairedDevices = success;
    },
      (err) => {

      })
  }

  selectDevice(address: any) {
    let alert = this.alertCtrl.create({
      title: 'Connect',
      message: 'Do you want to connect with?',
      buttons: [
        {
          text: 'Cancel',
          role: 'cancel',
          handler: () => {
            console.log('Cancel clicked');
          }
        },
        {
          text: 'Connect',
          handler: () => {
            this.bluetoothSerial.connect(address).subscribe(this.success, this.fail);
            
          }
        }
      ]
    });
    alert.present();

  }
  
  ionViewDidEnter(){
      this.isenabled=false; 

      this.bluetoothSerial.isConnected()
        .then(() => {
    this.isenabled=true; 
        }, (err) => {
        });
  
  }
}