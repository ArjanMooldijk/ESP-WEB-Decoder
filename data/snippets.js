const plaatjeHTML = '' +
    '<img src="{{sigType}}" height="80">';

const lampHTML = '' +
    '<div class="item2">' +
    '<div class="labelcontainer"> ' +
    '<label class="lichtLabel" for="lamp{{index}}">lichtsterkte lamp {{index}} (1 - 255): </label>' +
    '</div>' +
    '<div class="slidecontainer" id="slider"> ' +
    '<input  type="range" min="1" max="255" value="{{item}}" class="slider lampInput" id="lamp{{index}}">' +
    '<span id="sout" class="sout">{{item}}</span>' +
    '</div>' +
    '</div>';

const adresHTML = '' +
    '<div class="item2">' +
    '<div class="labelcontainer">' +
    '<label class="lichtLabel" for="adres{{index}}">{{adresString}}</label>' +
    '</div>' +
    '<div class="infocontainer" id="uitvoer">' +
    '<input class="infocontainer adresinput" type="number" name="adres{{index}}" id="adres{{index}}" value="{{item}}" disabled>' +
    '</div>' +
    '</div>';

const channelHTML = '' +
    '<div class="item2">' +
    '<div class="labelcontainer">' +
    '<label class="lichtLabel">Aantal draden :</label>' +
    '</div>' +
    '<div class="infocontainer" id="uitvoer">' +
    '<input class="infocontainer" type="number" name="draden" id="draden" value={{sigDraden}} disabled>' +
    '</div>' +
    '</div>' +
    '<div class="item2">' +
    '<div class="labelcontainer">' +
    '<label class="lichtLabel">Aansluiten vanaf </label>' +
    '</div>' +
    '<div class="infocontainer" id="uitvoer">' +
    '<input class="infocontainer" type="number" name="channel" id="channel" value="{{sigChannel}}" disabled>' +
    '</div>' +
    '</div>';

const fadeHTML = '' +
    '<div class="item2">' +
    '<div class="labelcontainer">' +
    '<label class="lichtLabel" for="fade">Fade tijd in (mSec): </label>' +
    '</div>' +
    '<div class="slidecontainer" id="slider">' +
    '<input type="range" min="0" max="50" value="{{cSfade10}}" class="slider" id="fade">' +
    '<span id="sout" class="sout">{{cSfade}}</span>' +
    '</div>' +
    '</div>' +
    '<div class="item2">' +
    '<div class="labelcontainer">' +
    '<label class="lichtLabel" for="dark">Donker tussen beelden (mSec): </label>' +
    '</div>' +
    '<div class="slidecontainer" id="slider">' +
    '<input type="range" min="0" max="50" value="{{cSdark10}}" class="slider" id="dark">' +
    '<span id="sout" class="sout">{{cSdark}}</span>' +
    '</div>' +
    '</div>';

const cleanChangeSignal = '' +
    '<div id="plaatContainer">'+
    '<div id="plaatFiller"></div>'+
    '<div id="imageC" class="plaatjeC">' +
    '</div>' +
    '</div>' +
    '<div class="s-display">' +
    '<form class=changeForm>' +
    '<div id=changeForm>' +
    '</div>' +
    '</form>' +
    '</div>';

const cleanHeader0 = '' +
    '<script id="header-template" type="text/template">' +
    '{{#h1}}' +
    '<h1>Seindecoder {{h1}}</h1>' +
    '<h2> Geen seinen aangesloten</h2>' +
    '{{/h1}}' +
    '</script>';

const cleanHeader1 = '' +
    '<script id="header-template" type="text/template">' +
    '{{#h1}}{{#h2}}' +
    '<h1>Seindecoder {{h1}}</h1>' +
    '<h2> {{h2}} sein aangesloten</h2>' +
    '{{/h2}}{{/h1}}' +
    '</script>';

const cleanHeader2 = '' +
    '<script id="header-template" type="text/template">' +
    '{{#h1}}{{#h2}}' +
    '<h1>Seindecoder {{h1}}</h1>' +
    '<h2> {{h2}} seinen aangesloten</h2>' +
    '{{/h2}}{{/h1}}' +
    '</script>';

const cleanAllConnected = '' +
    '<script id="signal-template" type="text/template">' +
    '{{#connSignal}}' +
    '<div class="signal-container">' +
    '<div id="image" class="plaatje">' +
    '<img src="{{sigType}}" width="auto" height="80px">' +
    '</div>' +
    '<div class="s-display">' +
    '<div class="s-data">' +
    '<p class="s-display">Type : {{sigType}} </p>' +
    '<p class="s-display">Aansluitingen : {{sigDraden}} </p>' +
    '<p class="s-display">Channel : {{sigChannel}} </p>' +
    '<p class="s-display">Adres : {{sigAdressen}} </p>' +
    '<p class="s-display">Fade : {{sigFade}} mSec</p>' +
    '<p class="s-display">Dark delay : {{sigDark}} mSec</p>' +
    '</div>' +
    '</div>' +
    '<div class="but-container">' +
    '<button id="{{sigId}}" class="sb-display sigBut">pas aan</button>' +
    '</div>' +
    '</div>' +
    '{{/connSignal}}' +
    '</script>';

const cleanNewSignal = '' +
    '<div class="full-line">' +
    '<p>Selecteer het aan te sluiten sein:</p>' +
    '</div>' +
    '<script id="seinen-template" type="text/template">' +
    '<form name="sigKeuze">' +
    '<h4 class="toggle-lijst">Voorseinen</h4>' +
    '<div id="sigKeuze">' +
    '{{#allVoorseinen}}' +
    '<input class="radio" type="radio" id="{{sigType}}" name="sigGekozen" value={{sigNbrAdr}}>' +
    '<label for="{{sigType}}">{{sigComment}}</label><br> {{/allVoorseinen}}' +
    ' <br>' +
    '</div>' +
    '<h4 class="toggle-lijst">Hoofdseinen</h4>' +
    '<div id="sigKeuze">' +
    '{{#allHoofdseinen}}' +
    '<input class="radio" type="radio" id="{{sigType}}" name="sigGekozen" value={{sigNbrAdr}}>' +
    '<label for="{{sigType}}">{{sigComment}}</label><br> {{/allHoofdseinen}}' +
    '<br>' +
    '</div>' +
    '<h4 class="toggle-lijst">Overige seinen</h4>' +
    '<div id="sigKeuze">' +
    '{{#allOverig}}' +
    '<input class="radio" type="radio" id="{{sigType}}" name="sigGekozen" value={{sigNbrAdr}}>' +
    '<label for="{{sigType}}">{{sigComment}}</label><br> {{/allOverig}}' +
    '<br>' +
    '</div>' +
    '</form>' +
    '</script>';