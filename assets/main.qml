
import bb.cascades 1.2
import bb.cascades.maps 1.0

TabbedPane {
    showTabsOnActionBar: true
    Tab { //First tab
        title: qsTr("Peek quest") + Retranslate.onLocaleOrLanguageChanged
        Page {
            Container {
                Button {
                    text: "Peek quest"
                    onClicked: {
                    }
                }
            }
        }
    } //End of first tab

    Tab { //Second tab
        // Localized text with the dynamic translation and locale updates support
        title: qsTr("Track Quest") + Retranslate.onLocaleOrLanguageChanged
        Page {
            Container {
                MapView {
                    id: mapView
                    horizontalAlignment: HorizontalAlignment.Fill
                    latitude: 56.2
                    longitude: 44.0
                }
            }
        }
    } //End of Second tab

}
