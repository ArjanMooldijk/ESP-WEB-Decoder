$(function() {

    //////////// Build main screen
    getDatafromServer();
    headers.makeHeader();
    mainScreen.makeMain();
});

// Get base dekoder data
var dekoder;
var typeSig;
var saveVal = {
    fade: null,
    dark: null,
    lamp: []
};
var changedValues = false;

function getDatafromServer() {
    //doe GET voor dekoder data
    dekoder = JSON.parse(deKoder);
    //doe GET voor signalen data
    typeSig = JSON.parse(typeSignalen);
};

function getObjects(obj, key, val) {
    var objects = [];
    for (var i in obj) {
        if (!obj.hasOwnProperty(i)) continue;
        if (typeof obj[i] == 'object') {
            objects = objects.concat(getObjects(obj[i], key, val));
        } else if (i == key && obj[key] == val) {
            objects.push(obj);
        }
    }
    return objects;
};

function showSliderVal() {
    return $(this).each(function() {
        if ($(this).attr("id") == "fade" || $(this).attr("id") == "dark") {
            var value = $(this).val() * 10;
        } else {
            var value = $(this).val()
        };
        $(this).next("#sout").html(value);

        if ($(this).attr("id") == "fade") {
            saveVal.fade = value;
        }
        if ($(this).attr("id") == "dark") {
            saveVal.dark = value;
        }
        if ($(this).attr("id") == "lamp1") {
            saveVal.lamp[0] = value;
        }
        if ($(this).attr("id") == "lamp2") {
            saveVal.lamp[1] = value;
        }
        if ($(this).attr("id") == "lamp3") {
            saveVal.lamp[2] = value;
        }
        if ($(this).attr("id") == "lamp4") {
            saveVal.lamp[3] = value;
        }

    })
};

var headers = function() {
    var data = {
        h1: "",
        h2: ""
    };
    var $el;
    var template;
    var firstTime = true;

    function _init() {
        data.h1 = dekoder.dekName;
        $el = $('.header-container');
        firstTime = false;
    };

    function _render() {
        data.h2 = dekoder.sigConnected.length;
        $($el).html(cleanHeader1);
        if (data.h2 == 0) {
            $($el).html(cleanHeader0);
        }
        template = $el.find('#header-template').html();
        $el.html(Mustache.render(template, data));
    };

    function makeHeader() {
        if (firstTime) {
            _init();
        };
        _render();
    };
    return {
        makeHeader: makeHeader
    }
}();

var mainScreen = (function() {
    var data = {
        connSignal: "",
    };
    var connSignal;
    var $el;
    var $al;
    var template;
    var firstTime = true;

    function _init() {
        $el = $('#connectedSignal');
        $al = $('.main-container');
        $al.delegate('#BNew', 'click', Nsein.newSignal);
        $al.delegate('#BStore', 'click', _storeValues);
        $el.delegate('.sigBut', 'click', _changeSig);
        firstTime = false;
        _render();
    };

    function _render() {
        data.connSignal = dekoder.sigConnected;
        $($el).html(cleanAllConnected);
        template = $el.find('#signal-template').html();
        $el.html(Mustache.render(template, data));
        $(".signal-set").show();
        $(".signal-types").hide();
        $(".signal-mutate").hide();
        if (changedValues) {
            $(".storebutton").show();
        } else {
            $(".storebutton").hide();
        };
        $(".NBcontainer").show();
        $(".signal-mutate").hide();
    };

    function _storeValues() {
        //doe post naar server
        changedValues = false;
        $(".storebutton").hide();
    }

    function _changeSig() {
        Csein.changeSignal($(this).attr('id'));
    };

    function makeMain() {
        if (firstTime) {
            _init();
        } else {
            _render();
        }

    };
    return {
        makeMain: makeMain
    };
})();

var Csein = (function() {
    var $el;
    var $fc;
    var signalToChange;
    var firstChange = true;

    function _init() {
        $el = $('#changeSignal');
        $fc = $('.footercontainer');
        $el.delegate('input.slider', 'input', showSliderVal);
        $fc.delegate('#BCancel', 'click', _cancelKeuze);
        $fc.delegate('#BDel', 'click', _deleteSignal);
        $fc.delegate('#BApply', 'click', _processValues);
        $fc.delegate('#BTest', 'click', _testLights);
        $fc.delegate('#BTestEnd', 'click', _endTestLights);
        firstChange = false;
    };


    function _prepareScreen(index) {
        $(".signal-set").hide();
        $(".NBcontainer").hide();
        $(".signal-mutate").show();
        if (index == (dekoder.sigConnected.length - 1)) {
            $("#BDel").show();
        } else {
            $("#BDel").hide();
        };
        $(".testbutTE").hide();
    };

    function _render() {
        var htmlPlaatje = Mustache.render(plaatjeHTML, signalToChange); // build plaatje                
        var htmlChannel = Mustache.render(channelHTML, signalToChange); // Build channel HTML

        // Build Adress HTML
        var htmlAdres = [];
        $.each(signalToChange.sigAdressen, function(index, item) {
            var waardes = {
                item: item,
                index: index + 1,
                adresString: ""
            }
            if (index == 0 && typeof signalToChange.sigAdressen[1] === 'undefined') {
                waardes.adresString = "Adres :";
            } else {
                var i = index + 1;
                waardes.adresString = "Adres " + i + ":";
            }
            htmlAdres[index] = Mustache.render(adresHTML, waardes);
        });

        // Build fade HTML
        var fadeWaardes = {
            cSfade10: signalToChange.sigFade / 10,
            cSdark10: signalToChange.sigDark / 10,
            cSfade: signalToChange.sigFade,
            cSdark: signalToChange.sigDark
        }
        var htmlFade = Mustache.render(fadeHTML, fadeWaardes);

        // Build Lamp HTML
        var htmlLamp = [];
        $.each(signalToChange.sigLamp, function(index, item) {
            var waardes = {
                item: item,
                index: index + 1
            }
            htmlLamp[index] = Mustache.render(lampHTML, waardes);
        });
        $($el).html(cleanChangeSignal);
        $el.find('#imageC').append(htmlPlaatje);
        $el.find('#changeForm').append(htmlChannel);
        $el.find('#changeForm').append(htmlAdres);
        $el.find('#changeForm').append(htmlFade);
        $el.find('#changeForm').append(htmlLamp);
    };

    function _processValues() {
        var i = signalToChange.sigId;
        dekoder.sigConnected[i].sigFade = saveVal.fade;
        dekoder.sigConnected[i].sigDark = saveVal.dark;

        var tmpLamp = $('.lampInput');
        $.each(tmpLamp, function(count, item) {
            dekoder.sigConnected[i].sigLamp[count] = saveVal.lamp[count];
        });
        changedValues = true;
        headers.makeHeader();
        mainScreen.makeMain();

    };

    function _testLights() {
        //call server met waardes van alle lampen
        $("#BApply").hide();
        $("#BDel").hide();
        $("#BCancel").hide();
        $(".testbutTE").show();
    }

    function _endTestLights() {
        //call server met waardes van alle lampen
        $("#BApply").show();
        $("#BDel").show();
        $("#BCancel").show();
        $(".testbutTE").hide();
    }

    function _cancelKeuze() {
        setMainScreen();
        // _cleanInput();
        // $(".signal-set").show();
        // $(".newbutton").show();
        // $(".signal-mutate").hide();
    };

    function _deleteSignal() {
        dekoder.sigConnected.pop();
        changedValues = true;
        setMainScreen();
    };

    function setMainScreen() {
        headers.makeHeader();
        mainScreen.makeMain();
    };

    function changeSignal(index) {
        $(".signal-set").hide();
        $(".NBcontainer").hide();
        $(".signal-mutate").show()
        if (firstChange) {
            _init();
        };
        signalToChange = dekoder.sigConnected[index];
        saveVal.lamp = signalToChange.sigLamp;
        saveVal.fade = signalToChange.sigFade;
        saveVal.dark = signalToChange.sigDark;
        _prepareScreen(index);
        _render();

    };

    return {
        changeSignal: changeSignal
    };
})();

var Nsein = (function() {
    var seinType;
    var data = {
        allVoorseinen: [],
        allHoofdseinen: [],
        allOverig: []
    };
    var $el;
    var $sc;
    var template;
    var firstTime = true;

    function _init() {
        data.allVoorseinen = getObjects(typeSig, 'sigHoofdtype', 'voorsein');
        data.allHoofdseinen = getObjects(typeSig, 'sigHoofdtype', 'hoofdsein');
        data.allOverig = getObjects(typeSig, 'sigHoofdtype', 'overig');
        $el = $('#allTypes');
        $sc = $('#signal-config');
        $el.delegate('input:radio[name=sigGekozen]', 'click', _showAdresInput);
        $sc.delegate('input.slider', 'input', showSliderVal);
        $el.delegate('#BKeuze', 'click', _processKeuze);
        $el.delegate('#BCancel', 'click', _cancelKeuze.bind(this));
        firstTime = false;
        _render();
    };

    function _render() {
        $($el).html(cleanNewSignal);
        template = $el.find('#seinen-template').html();
        $el.html(Mustache.render(template, data));
        $(".1adres").hide();
        $(".2adres").hide();
        $(".3adres").hide();
        _cleanInput();
        $(".signal-set").hide();
        $(".NBcontainer").hide();
        $(".instellingen").hide();
        $(".signal-types").show();
    };

    function _showAdresInput() {
        var value = $(this).val();
        seinType = "";
        seinType = $(this).attr('id');
        if (value == 1) {
            $(".2adres").hide();
            $(".3adres").hide();
            $(".1adres").show();
        } else {
            if (value == 2) {
                $(".1adres").hide();
                $(".3adres").hide();
                $(".2adres").show();
            } else {
                $(".1adres").hide();
                $(".2adres").hide();
                $(".3adres").show();
            }
        }
        $(".instellingen").show();
    };

    function _processKeuze() {
        var selSignalType = getObjects(typeSig, 'sigType', seinType);
        if (dekoder.sigConnected.length == 0) {
            var nextId = 0;
            var nextChannel = 0;
        } else {
            var nextId = dekoder.sigConnected[dekoder.sigConnected.length - 1].sigId + 1
            var nextChannel = dekoder.sigConnected[dekoder.sigConnected.length - 1].sigDraden +
                dekoder.sigConnected[dekoder.sigConnected.length - 1].sigChannel
        };
        if (nextChannel + selSignalType[0].sigDraden > 16) {
            alert('te weinig aansluitingen voor dit sein op de decoder!');
            return;
        }
        var newSignal = {
            "sigId": nextId,
            "sigType": seinType,
            "sigDraden": selSignalType[0].sigDraden,
            "sigChannel": nextChannel,
            "sigAdressen": [parseInt($("#adres1").val())],
            "sigImage": selSignalType[0].sigImage,
            "sigFade": $("#fade").val() * 10,
            "sigDark": $("#dark").val() * 10,
            "sigLamp": [200]
        };

        tmpAdr = $('.adresInput');
        $.each(tmpAdr, function(index, item) {
            newSignal.sigAdressen[index] = parseInt($(item).val());
        });

        for (var i = 0; i < newSignal.sigDraden; i++) {
            newSignal.sigLamp[i] = 200;
        };
        dekoder.sigConnected.push(newSignal);
        changedValues = true;

        headers.makeHeader();
        mainScreen.makeMain();

    };

    function _cancelKeuze() {
        _cleanInput();
        $(".signal-set").show();
        $(".NBcontainer").show();
        $(".signal-types").hide();
    };

    function _cleanInput() {
        var allRadio = $($el).find('.radio');
        $.each(allRadio, function(index, item) {
            $(item).prop('checked', false);
        });
        var allFade = $($sc).find('#fade');
        $(allFade).val(15);
        $(allFade).next("#sout").html(150);

        var allDark = $($sc).find('#dark');
        $(allDark).val(30);
        $(allDark).next("#sout").html(300);

        var allAdr = $($sc).find('.adresInput');
        $.each(allAdr, function(index, item) {
            $(item).val("");
        });
    };

    function newSignal() {
        if (firstTime) {
            _init();
        } else {
            _render();
        }
    };
    return {
        newSignal: newSignal
    };

})();