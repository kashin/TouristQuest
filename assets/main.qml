
import bb.cascades 1.2
import bb.cascades.maps 1.0
import mobile.quest 1.0

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
                Button {
                    text: "save data"
                    onClicked: {
                        questData.saveQuest();
                    }
                }
                Button {
                    text: "load data"
                    onClicked: {
                        statusLabel3.text = "start"
                        questData.name = "test"
                        statusLabel3.text = "2"
                        statusLabel2.text = "questDataName=" + questData.name
                        statusLabel3.text = "3"
                        statusLabel.text += questData.questID
                        statusLabel3.text = "4"
                    }
                }
                Label {
                    id: statusLabel
                    text: "questID="
                }
                Label {
                    id: statusLabel2
                    text: "questDataName="
                }
                Label {
                    id: statusLabel3
                    text: "nothing"
                }
                QuestMap {
                    id: mapView
                    horizontalAlignment: HorizontalAlignment.Fill
/*                    latitude: 56.2
                    longitude: 44.0*/
                    questData: QuestData {
                        id: questData
                    }
                }
            }
        }
    } //End of Second tab

}
