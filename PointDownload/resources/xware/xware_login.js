Point.sJSLogin.connect(pointSlotLogin);
Point.sJSUpdateVertifyCode.connect(pointUpdateVertifyCode);

var spliterBtwData = "#..#";
var spliterEnd = "#.^_^.#";

var pointLoginCheckInterval;

var pointVertifyChangeIntervalId;

// login frame
$p_lf = $("#loginIframe").contents();

function pointSlotLogin(userName, pwd, vertifyCode)
{
    $p_lf.find("#al_c").val(vertifyCode);
    $p_lf.find("#al_u").val(userName);
    $p_lf.find("#al_p").val(pwd);
    $p_lf.find("#al_c").val(vertifyCode);

    setTimeout(
    function()
    {
        // debug
        Point.justForJSTest("login");

        $p_lf.find("#al_submit").get(0).click();
    }, 500
    );
}

var pointLoginCheckValid = true;  // whether login check valid flag
pointLoginCheckInterval = setInterval("pointLoginCheckSlot()", 500);
// check login even (pwd incorrect, username not exist ...)
function pointLoginCheckSlot()
{
    if($p_lf.find("#al_warn").css("display") === "block")
    {
        if(pointLoginCheckValid)
        {
            Point.loginError(1, $p_lf.find("#al_warn").html());
        }
        pointLoginCheckValid = false;
    }
    else
    {
        pointLoginCheckValid = true;
    }
}

pointVertifyChangeIntervalId = setInterval("pointVertifyCodeCheckSlot()", 200);
var lastVc = ""
function pointVertifyCodeCheckSlot()
{
    var vc = $p_lf.find("#al_c_img").attr("src")
    if(vc !== lastVc)
    {
        Point.justForJSTest("pointVertifyCodeCheckSlot: " + vc)
        Point.loginError(2,  vc);
        lastVc = vc;
    }
}

function pointUpdateVertifyCode()
{
    $p_lf.find("#al_c_img").click();
}



