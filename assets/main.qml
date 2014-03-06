
import bb.cascades 1.2
import bb.cascades.maps 1.0

TabbedPane {
    showTabsOnActionBar: true
    Tab { //First tab
        // Localized text with the dynamic translation and locale updates support
        title: qsTr("Track Quest") + Retranslate.onLocaleOrLanguageChanged
        Page {
            Container {
                Button {
                    text: "Peek quest"
                    onClicked: {
                    }
                }
                MapView {
                    id: mapView
                    horizontalAlignment: HorizontalAlignment.Fill
                    latitude: 56.2
                    longitude: 44.0
                }
            }
        }
    } //End of first tab
    Tab { //Second tab
        title: qsTr("Quest description") + Retranslate.onLocaleOrLanguageChanged
        Page {
            Container {
                Label {
                    text: qsTr("Second tab") + Retranslate.onLocaleOrLanguageChanged
                }
            }
        }
    } //End of second tab
}
