<!-- DOC HelpContext="Netzwerk" -->
# Applikationsbeschreibung Netzwerk 

Im Bereich Netzwerk werden die für die Netzwerkverbindung notewendigen Einstellung und Basisnetzwerkdienste konfiguriert.

<!-- DOC Skip="1" -->
Hinweis: Nicht alle der hier angeführten Optionen sind in jeder Firmware verhanden. 

<!-- DOC -->
## Allgemein

In diesem Abschnitt werden die Basiseinstellungen und verfügbaren Dienste festgelegt.

<!-- DOC -->
### IP-Adresse

In diesem Eingabeformular kannst du entscheiden, ob die IP-Adresse dynamisch durch einen DHCP-Server zugewiesen oder manuell festgelegt werden soll. Bei manueller Konfiguration sind neben der IP-Adresse auch die Netzmaske, ein Standardgateway (Router) und ein Nameserver (DNS) erforderlich.

<!-- DOC -->
### Services

<!-- DOC HelpContext="mDNS-Service" -->
### mDNS

Der mDNS Service ermöglicht das Auflösen von "Hostname.local" und kann auch später zum Auffinden von OpenKNX-Geräten im eigenen Netzwerk genutzt werden.

<!-- DOC -->
### Erweitere Einstellungen

In diesem Abschnitt werden Einstellungen vorgenommen die vorwiegen von Netzwerkexperten benötigt werden.

<!-- DOC -->
### Hostname anpassen

Legt fest ob der Standardgerätename verwendet wird oder ob der Hostnamen individuell konfiuriert wird.

<!-- DOC -->
### Hostname

Der Hostname wird automatisch aus der Seriennummer generiert (OpenKNX-XXXXXXXX) und erfordert in der Regel keine Anpassung. Sollte jedoch eine individuelle Anpassung gewünscht sein, darf die Länge von 24 Zeichen nicht überschritten werden. Darüber hinaus sind nur Buchstaben, Zahlen und Bindestriche erlaubt. Der Hostname muss zudem mit einem Buchstaben beginnen und darf nicht mit einem Bindestrich enden.

<!-- DOC -->
## LAN-Modus
(Diese Option wir bei WLAN Geräten ignoriert!)

Wähle den gewünschten Modus für die LAN-Schnittstelle aus. Die Auswahl des 10 MBit/s Modus kann genutzt werden, um den Stromverbrauch zu reduzieren.

**Hinweis**: In neueren Switches mit Geschwindigkeiten ab 2,5 GBit/s ist der 10 MBit/s Modus in der Regel nicht mehr vorgesehen. Es besteht daher die Möglichkeit, dass in solchen Fällen keine Verbindung hergestellt werden kann. Dennoch lohnt es sich, dies auszuprobieren, da einige Geräte diesen Modus unterstützen.

<!-- DOC -->
### WiFi-Assistent

Dieser WiFi-Assistent ermöglicht das Übertragen von WiFi-Zugangsdaten auf das Gerät. Voraussetzung ist, dass die verwendete Hardware einen WiFi-Adapter verwendet. Geräte, die per IP-Netzwerk angebunden werden, müssen bereits über eine WiFi-Verbindung und somit über gültige Zugangsdaten verfügen. Der Assistent kann daher nur die bestehenden Zugangsdaten ändern. TP-Geräte können hingegen immer per Bus angepasst werden.

IP-Geräte ohne WiFi-Zugangsdaten müssen initial auf anderem Wege eingerichtet werden. Dies hängt sowohl von der Gerätesoftware als auch der verwendeten Hardware ab. Die Einrichtung per Terminal (USB) sollte immer funktionieren. Dafür muss auf der Konsole nur "wifi SSID PSK" eingegeben werden.

Bei Geräten auf Arduino-Pico-Basis können die WiFi-Zugangsdaten in der Regel zusätzlich per USB übertragen werden. Dazu muss das Gerät am Rechner angeschlossen und der Transfermodus durch einen Doppelklick auf die Prog-Taste gestartet werden. Kopiere dann eine Datei namens "WIFI.TXT" auf das Wechsellaufwerk. Die erste Zeile muss die SSID und die zweite den PSK enthalten. Danach den Modus wieder mit einem Doppelklick beenden und das Gerät neu starten.

<!-- DOC -->
# Zeitgeber

Unter Zeitgeber können Zeit-Server aus dem Internet konfiguriert werden. 
Über diese wird zyklisch die aktuell Uhrzeit und das Datum abgerufen.
Uhrzeit und Datum kann je nach Konfiguration auch auf dem Bus zur Verfügung gestellt werden.
In einem KNX Netz sollte sich ein Zeitgeber befinden.

<!-- DOC -->
### NTP Server

Gibt den Zeitserver (NTP) an, von dem die Uhrzeit abgerufen wird.
Meist wird ein Pool aus Zeitservern verwendet.
Der DNS liefert einer der IP Adressen des Pools aus.

Beispiel: pool.ntp.org

Weiter Informationen und freie Verfügbare Zeitserver sind auf der Website https://www.ntppool.org zu finden.

<!-- DOC -->
## Webserver

Diese Funktion steht derzeit noch nicht zur Verfügung.