<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="vi" lang="vi" dir="ltr">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta content="http://diendan.congdongcviet.com" />
	<base href="http://diendan.congdongcviet.com/" /><!--[if IE]></base><![endif]-->
	<meta name="generator" content="Diễn đàn Cộng đồng C Việt @ 2014" />
	<link rel="shortcut icon" href="favicon.ico" type="image/x-icon" />

	<meta name="keywords" content="Lap trinh C,Lap trinh C++,Lap trinh C#, Lap trinh Java, Lap trinh iOS, Lap trinh Android, Lap trinh Linux, Ma nguon,Computer programming,Software Engineering,Cong nghe phan mem,ANSI C,ISO C++,Visual C++,VC++,C++.NET,C++Builder,DEV-CPP,C#,C-Sharp,Thuật toán trên C/C++,Database,Linux,Unix Kernel,php,ASP.NET" />
	<meta name="description" content="Lập trình C, Lập trình C++, Lập trình C#, Lập trình Java, Lập trình iOS, Lập trình Android, Lập trình Linux, Mã nguồn, ... và phát triển ứng dụng CNTT tại Việt Nam. Cộng đồng lập trình lớn nhất Việt Nam." />



<script type="text/javascript">
<!--
	if (typeof YAHOO === 'undefined') // Load ALL YUI Local
	{
		document.write('<script type="text/javascript" src="clientscript/yui/yuiloader-dom-event/yuiloader-dom-event.js?v=422"><\/script>');
		document.write('<script type="text/javascript" src="clientscript/yui/connection/connection-min.js?v=422"><\/script>');
		var yuipath = 'clientscript/yui';
		var yuicombopath = '';
		var remoteyui = false;
	}
	else // Load Rest of YUI remotely (where possible)
	{
		var yuipath = 'clientscript/yui';
		var yuicombopath = '';
		var remoteyui = true;
		if (!yuicombopath) document.write('<script type="text/javascript" src="clientscript/yui/connection/connection-min.js"><\/script>');
	}
	var SESSIONURL = "";
	var SECURITYTOKEN = "guest";
	var IMGDIR_MISC = "images/misc";
	var IMGDIR_BUTTON = "images/buttons";
	var vb_disable_ajax = parseInt("0", 10);
	var SIMPLEVERSION = "422";
	var BBURL = "http://diendan.congdongcviet.com/";
	var LOGGEDIN = 0 > 0 ? true : false;
	var THIS_SCRIPT = "attachment";
	var RELPATH = "attachment.php?attachmentid=5373&amp;stc=1&amp;d=1299055314";
	var PATHS = {
		forum : "http://diendan.congdongcviet.com",
		cms   : "",
		blog  : ""
	};
	var AJAXBASEURL = "http://diendan.congdongcviet.com/";
// -->
</script>
<script type="text/javascript" src="http://diendan.congdongcviet.com/clientscript/vbulletin-core.js?v=422"></script>



	<link rel="alternate" type="application/rss+xml" title="Cộng đồng C Việt RSS Feed" href="http://diendan.congdongcviet.com/external.php?type=RSS2" />
	



	<link rel="stylesheet" type="text/css" href="clientscript/vbulletin_css/style00004l/main-rollup.css?d=1486562733" />
	

	<!--[if lt IE 8]>
	<link rel="stylesheet" type="text/css" href="clientscript/vbulletin_css/style00004l/popupmenu-ie.css?d=1486562733" />
	<link rel="stylesheet" type="text/css" href="clientscript/vbulletin_css/style00004l/vbulletin-ie.css?d=1486562733" />
	<link rel="stylesheet" type="text/css" href="clientscript/vbulletin_css/style00004l/vbulletin-chrome-ie.css?d=1486562733" />
	<link rel="stylesheet" type="text/css" href="clientscript/vbulletin_css/style00004l/vbulletin-formcontrols-ie.css?d=1486562733" />
	<link rel="stylesheet" type="text/css" href="clientscript/vbulletin_css/style00004l/editor-ie.css?d=1486562733" />
	<![endif]-->
	<link rel="stylesheet" type="text/css" href="http://diendan.congdongcviet.com/clientscript/cviet_bbcode.css" />

	<meta name="robots" content="noindex,follow" />
	<title>Cộng đồng C Việt</title>
	<script type="text/javascript" src="http://diendan.congdongcviet.com/clientscript/vbulletin_md5.js?v=422"></script>
	
	<link rel="stylesheet" type="text/css" href="clientscript/vbulletin_css/style00004l/additional.css?d=1486562733" />

</head>
<body>
<div class="above_body"> <!-- closing tag is in template navbar -->
<div id="toplinks" class="toplinks clearfix">

	<ul class="nouser">
		<li><a rel="help" href="faq.php">Help</a></li>
		
			<li><a href="register.php" rel="nofollow">Đăng ký</a></li>
		
		<li>
		<script type="text/javascript" src="http://diendan.congdongcviet.com/clientscript/vbulletin_md5.js?v=422"></script>
		<form id="navbar_loginform" action="login.php?do=login" method="post" onsubmit="md5hash(vb_login_password, vb_login_md5password, vb_login_md5password_utf, 0)">
			<fieldset id="logindetails" class="logindetails">
				<div>
					<input type="text" class="textbox default-value" name="vb_login_username" id="navbar_username" size="10" accesskey="u" tabindex="101" value="Username" />
					<input type="password" class="textbox" tabindex="102" name="vb_login_password" id="navbar_password" size="10" />
					<input type="text" class="textbox default-value" tabindex="102" name="vb_login_password_hint" id="navbar_password_hint" size="10" value="Password" style="display: none;" />
					<input type="submit" class="loginbutton" tabindex="104" value="Log in" title="Nhập vào username và password của bạn trong các hộp đã cung cấp để đăng nhập, hoặc click vào 'register' button để tạo một hồ sơ cho bạn." accesskey="s" />
					<label for="cb_cookieuser_navbar">
						<input type="checkbox" name="cookieuser" value="1" id="cb_cookieuser_navbar" class="cb_cookieuser_navbar" accesskey="c" tabindex="103" /> Nhớ tôi vào?
					</label>
				</div>
			</fieldset>
			
			<input type="hidden" name="s" value="" />
			<input type="hidden" name="securitytoken" value="guest" />
			<input type="hidden" name="do" value="login" />
			<input type="hidden" name="vb_login_md5password" />
			<input type="hidden" name="vb_login_md5password_utf" />
		</form>
	<script type="text/javascript">
	YAHOO.util.Dom.setStyle('navbar_password_hint', "display", "inline");
	YAHOO.util.Dom.setStyle('navbar_password', "display", "none");
	vB_XHTML_Ready.subscribe(function()
	{
	//
		YAHOO.util.Event.on('navbar_username', "focus", navbar_username_focus);
		YAHOO.util.Event.on('navbar_username', "blur", navbar_username_blur);
		YAHOO.util.Event.on('navbar_password_hint', "focus", navbar_password_hint);
		YAHOO.util.Event.on('navbar_password', "blur", navbar_password);
	});
	
	function navbar_username_focus(e)
	{
	//
		var textbox = YAHOO.util.Event.getTarget(e);
		if (textbox.value == 'Username')
		{
		//
			textbox.value='';
			textbox.style.color='#000000';
		}
	}

	function navbar_username_blur(e)
	{
	//
		var textbox = YAHOO.util.Event.getTarget(e);
		if (textbox.value == '')
		{
		//
			textbox.value='Username';
			textbox.style.color='#777777';
		}
	}
	
	function navbar_password_hint(e)
	{
	//
		var textbox = YAHOO.util.Event.getTarget(e);
		
		YAHOO.util.Dom.setStyle('navbar_password_hint', "display", "none");
		YAHOO.util.Dom.setStyle('navbar_password', "display", "inline");
		YAHOO.util.Dom.get('navbar_password').focus();
	}

	function navbar_password(e)
	{
	//
		var textbox = YAHOO.util.Event.getTarget(e);
		
		if (textbox.value == '')
		{
			YAHOO.util.Dom.setStyle('navbar_password_hint', "display", "inline");
			YAHOO.util.Dom.setStyle('navbar_password', "display", "none");
		}
	}
	</script>
		</li>
		
	</ul>

</div>
<div id="header" class="doc_header clearfix">
	
	<div class="logo">
		<a name="top" href="http://diendan.congdongcviet.com/forum.php" class="logo-image" title="Cộng đồng C Việt - Lập trình C, Lập trình C++, Lập trình C#, Lập trình Java, Lập trình iOS, Lập trình Android, Lập trình Linux, Mã nguồn ... Phát triển ứng dụng CNTT tại Việt Nam">
			<img src="images/logos/cviet_logo.png" alt="Cộng đồng C Việt" />
		</a>
	</div>
	
	<div class="ad_global_header">
		
		<div id="ad_global_header2"><div id="head_banner" style="position: relative; margin: 0 auto; top: 0px; left: 0px; width: 728px; height: 90px; overflow: hidden; visibility: hidden;">
        <div style="position: absolute; top: 0px; left: 0px;" data-u="loading">
            <div style="filter: alpha(opacity=70); opacity: 0.7; position: absolute; display: block; top: 0px; left: 0px; width: 100%; height: 100%;"></div>
            <div style="position:absolute;display:block;background:url('images/slider/loading.gif') no-repeat center center;top:0px;left:0px;width:100%;height:100%;"></div>
        </div>
        <div data-u="slides" style="cursor: default; position: relative; top: 0px; left: 0px; width: 728px; height: 90px; overflow: hidden;">
			<div style="display: block;" data-p="112.50">
				<!-- CViet TopHeader -->
				<ins class="adsbygoogle"
					 style="display:block"
					 data-ad-client="ca-pub-2525409910423371"
					 data-ad-slot="6395038884"
					 data-ad-format="auto"></ins>
				<script>
				(adsbygoogle = window.adsbygoogle || []).push({});
				</script>
            </div>
        </div>
        <div class="bullet_slider" style="bottom:8px;right:8px;" data-u="navigator" data-autocenter="0">
            <div style="width:16px;height:16px;" data-u="prototype"></div>
        </div>
        <span class="slider_arrow_left" style="top:0px;left:8px;width:40px;height:40px;" data-u="arrowleft" data-autocenter="2"></span>
        <span class="slider_arrow_right" style="top:0px;right:8px;width:40px;height:40px;" data-u="arrowright" data-autocenter="2"></span>
    </div></div>
	</div>
</div>
<div id="navbar" class="navbar">
	<ul id="navtabs" class="navtabs clearfix">
		
		

<li id="vbtab_whatsnew">
	<a class="navtab" href="activity.php">What's New?</a>

	
</li>


<li id="vbtab_forum" class="selected">
	<a class="navtab" href="forum.php">Tất cả diễn đàn</a>

	
	<ul class="clearfix">
		
			
				
					<li id="vbflink_newposts"><a href="search.php?do=getnew&amp;contenttype=vBForum_Post&amp;exclude=37,45,69">Các bài viết mới</a></li>
				
			
		
			
				
					<li id="vbflink_calendar"><a href="calendar.php">Lịch</a></li>
				
			
		
			
				<li class="popupmenu" id="vbmenu_actions">
					<a href="javascript://" class="popupctrl">Forum Actions</a>
					<ul class="popupbody popuphover">
						
							<li id="vbalink_mfr"><a href="forumdisplay.php?do=markread&amp;markreadhash=guest">Đánh dấu các diễn đàn là đã đọc</a></li>
						
					</ul>
				</li>
			
		
			
				<li class="popupmenu" id="vbmenu_qlinks">
					<a href="javascript://" class="popupctrl">Quick Links</a>
					<ul class="popupbody popuphover">
						
							<li id="vbqlink_posts"><a href="search.php?do=getdaily&amp;contenttype=vBForum_Post">Các bài viết hôm nay</a></li>
						
							<li id="vbqlink_leaders"><a href="showgroups.php">View Site Leaders</a></li>
						
					</ul>
				</li>
			
		
	</ul>
	
</li>


<li id="tab_odg4_564">
	<a class="navtab" href="http://diendan.congdongcviet.com/forums/f54::nhap-mon-lap-trinh-c-cpp.cpp?tabid=28">Lập trình cho người mới</a>

	
</li>


<li id="tab_odg4_125">
	<a class="navtab" href="http://diendan.congdongcviet.com/forums/f31::tutorials-thu-thuat-lap-trinh-csharp-asp-net.cpp?tabid=30">Tutorials &amp; Thủ thuật</a>

	
</li>

		
	</ul>
	
		<div id="globalsearch" class="globalsearch">
			<form id="navbar_search" class="navbar_search clearfix" action="search.php?do=process" method="post">
				
				<input type="hidden" name="securitytoken" value="guest" />
				<input type="hidden" name="do" value="process" />
				<span class="textboxcontainer"><input type="text" value="" name="query" class="textbox" tabindex="99"/></span>
				<span class="buttoncontainer"><input type="image" class="searchbutton" src="images/buttons/search.png" name="submit" onclick="document.getElementById('navbar_search').submit;" tabindex="100"/></span>
			</form>
			<ul class="navbar_advanced_search">
				<li><a href="search.php" accesskey="4">Tìm kiếm cao cấp &raquo;</a></li>
				
			</ul>
		</div>
	
</div>
</div><!-- closing div for above_body -->

<div class="body_wrapper">
<div class="breadcrumb">
	<ul class="clearfix">
		<li class="navbithome"><a href="http://diendan.congdongcviet.com/" accesskey="1"><img src="images/misc/navbit-home.png" alt="Home" /></a></li>
		
		

	<li class="navbit lastnavbit"><span>Cộng đồng C Việt thông báo</span></li>

	</ul>
	<hr />
</div>


<div id="ad_global_below_navbar"><div id="nav_banner" style="position: relative; margin: 0 auto; top: 0px; left: 0px; height: 90px; overflow: hidden; visibility: hidden;">
        <div style="position: absolute; top: 0px; left: 0px;" data-u="loading">
            <div style="filter: alpha(opacity=70); opacity: 0.7; position: absolute; display: block; top: 0px; left: 0px; width: 100%; height: 100%;"></div>
            <div style="position:absolute;display:block;background:url('images/slider/loading.gif') no-repeat center center;top:0px;left:0px;width:100%;height:100%;"></div>
        </div>
        <div data-u="slides" style="cursor: default; position: relative; top: 0px; left: 0px; width: 728px; height: 90px; overflow: hidden;">
			<div style="display: block;" data-p="112.50">
				<!-- CViet Navbar -->
				<ins class="adsbygoogle"
					 style="display:block"
					 data-ad-client="ca-pub-2525409910423371"
					 data-ad-slot="9033790880"
					 data-ad-format="auto"></ins>
				<script>
				(adsbygoogle = window.adsbygoogle || []).push({});
				</script>
            </div>
        </div>
        <div class="bullet_slider" style="bottom:8px;right:8px;" data-u="navigator" data-autocenter="0">
            <div style="width:16px;height:16px;" data-u="prototype"></div>
        </div>
        <span class="slider_arrow_left" style="top:0px;left:8px;width:40px;height:40px;" data-u="arrowleft" data-autocenter="2"></span>
        <span class="slider_arrow_right" style="top:0px;right:8px;width:40px;height:40px;" data-u="arrowright" data-autocenter="2"></span>
    </div>
	<script type="text/javascript" src="clientscript/slider/jssor.slider.min.js"></script>
    <script type="text/javascript">
        bannerSlider_init = function() {
            
            var bannerSlideshowTransitions = [
              {$Duration:3000,x:-0.3,$During:{$Left:[0.3,0.7]},$Easing:{$Left:$Jease$.$InCubic,$Opacity:$Jease$.$Linear},$Opacity:2},
              {$Duration:3000,x:0.3,$SlideOut:true,$Easing:{$Left:$Jease$.$InCubic,$Opacity:$Jease$.$Linear},$Opacity:2}
            ];
            
            var bannerOptions = {
              $AutoPlay: true,
              $SlideshowOptions: {
                $Class: $JssorSlideshowRunner$,
                $Transitions: bannerSlideshowTransitions,
                $TransitionsOrder: 1
              },
              $ArrowNavigatorOptions: {
                $Class: $JssorArrowNavigator$
              },
              $BulletNavigatorOptions: {
                $Class: $JssorBulletNavigator$
              },
              $ThumbnailNavigatorOptions: {
                $Class: $JssorThumbnailNavigator$,
                $Cols: 1,
                $Align: 0,
                $NoDrag: true
              }
            };
            
            var bannerSlider = new $JssorSlider$("head_banner", bannerOptions);
			bannerSlider = new $JssorSlider$("nav_banner", bannerOptions);
        };
    </script>
    <script type="text/javascript">bannerSlider_init();</script></div>


<div class="standard_message">
	<h2 class="blockhead">Cộng đồng C Việt thông báo</h2>
	
		<form class="block vbform"  method="post" action="login.php?do=login" onsubmit="md5hash(vb_login_password, vb_login_md5password, vb_login_md5password_utf, 0)">	
			<input type="hidden" name="do" value="login" />
			<input type="hidden" name="vb_login_md5password" value="" />		
			<input type="hidden" name="vb_login_md5password_utf" value="" />
			<input type="hidden" name="s" value="" />
			<input type="hidden" name="securitytoken" value="guest" />			
					
			
				
					<input type="hidden" name="url" value="http://diendan.congdongcviet.com/attachment.php?attachmentid=5373&amp;stc=1&amp;d=1299055314" />
				
				<div class="blockbody formcontrols clearfix">
					
					<h3 class="blocksubhead">Bạn chưa đăng nhập hoặc bạn không có quyền truy cập trang này. Điều này có thể do một vài lý do sau đây:</h3>
					<div class="blockrow restore">
						<ol>
							<li>Bạn chưa đăng nhập. Điền vào biểu mẫu ở cuối trang này và thử lại lần nữa.</li>
							<li>Bạn có lẽ không có đủ đặc quyền để truy cập trang này. Có phải bạn đang thử chỉnh sửa bài viết của người nào đó, truy cập tới các chức năng quản trị hoặc vài hệ thống đặc quyền khác không?</li>
							<li>Nếu bạn đang thử gửi bài viết, administrator có thể đã vô hiệu hóa tài khoản của bạn, hoặc nó có thể đang đợi sự kích hoạt của bạn.</li>
						</ol>
					</div>
					
					<p class="blockrow">Administrator có thể đòi hỏi bạn phải <a href="" rel="nofollow">đăng ký</a> trước khi bạn có thể xem trang này.</p>					
					<h3 class="blocksubhead">Log in</h3>		
					<div class="blockrow clearfix">
						<label for="vb_login_username">Username:</label>
						<input type="text" class="textbox primary" id="vb_login_username" name="vb_login_username" accesskey="u" tabindex="1" />
					</div>
					<div class="blockrow clearfix">			
						<label for="vb_login_password">Password:</label>
						<input type="password" class="textbox primary" id="vb_login_password" name="vb_login_password" tabindex="1" />
					</div>
					<div class="blockrow singlecheck">
						<label class="loginremember" for="cb_cookieuser"><input type="checkbox" name="cookieuser" id="cb_cookieuser" value="1" tabindex="1" /> Nhớ tôi vào?</label>
					</div>					
				</div>
				<div class="blockfoot actionbuttons">
					<div class="group">
						<input type="submit" class="button" value="Log in" accesskey="s" tabindex="1" />
						<input type="reset" class="button" value="Thiết lập lại các trường" accesskey="r" tabindex="1" />
					</div>
				</div>
			
	</form>		
	
</div>
<div class="forumjump_ctrl clearfix">
<div class="navpopupmenu popupmenu nohovermenu" id="navpopup">
	
		<a href="javascript://" class="popupctrl"><span class="ctrlcontainer">Quick Navigation</span></a>
	
	<ul class="navpopupbody popupbody popuphover">
		<li class="optionlabel">Các khu vực của site</li>
		<li><a href="usercp.php">Settings</a></li>
		<li><a href="private.php">Tin nhắn</a></li>
		<li><a href="http://diendan.congdongcviet.com/subscription.php">Các theo dõi</a></li>
		<li><a href="online.php">Ai online</a></li>
		<li><a href="search.php">Tìm kiếm các diễn đàn</a></li>
		<li><a href="http://diendan.congdongcviet.com/forum.php">Trang chính</a></li>
		
			<li class="optionlabel">Các diễn đàn</li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f1::cong-dong-c-viet.cpp">CỘNG ĐỒNG C VIỆT</a>
					<ol class="d1">
						
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f2::thong-bao-chung.cpp">Thông báo chung</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f3::y-kien-de-xuat-khieu-nai.cpp">Ý kiến, đề xuất và khiếu nại</a></li>
			
		
			
					</ol>
				</li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f32::dinh-huong-dao-tao-viec-lam-nganh-cntt.cpp">ĐỊNH HƯỚNG, ĐÀO TẠO &amp; VIỆC LÀM NGÀNH CNTT</a>
					<ol class="d1">
						
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f55::dao-tao-cntt.cpp">Đào tạo CNTT</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f19::kinh-nghiem-cntt.cpp">Kinh nghiệm CNTT</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f15::hoi-thao-chuyen-de-cac-cuoc-thi-cntt.cpp">Hội thảo, Chuyên đề và Các cuộc thi CNTT</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f49::tuyen-dung-viec-lam-cntt.cpp">Tuyển dụng - Việc làm CNTT</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f52::viec-lam-it-tu-do.cpp">Việc làm IT(tự do)</a></li>
			
		
			
					</ol>
				</li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f9::lap-trinh-visual-csharp.cpp">LẬP TRÌNH VISUAL C#</a>
					<ol class="d1">
						
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f17::thac-mac-lap-trinh-csharp.cpp">Thắc mắc lập trình C#</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f46::thac-mac-lap-trinh-asp-net.cpp">Thắc mắc lập trình ASP.NET</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f47::lap-trinh-windows-mobile-bang-csharp.cpp">Lập trình Windows Mobile bằng C#</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f31::tutorials-thu-thuat-lap-trinh-csharp-asp-net.cpp">Tutorials và Thủ thuật lập trình C#, ASP.NET</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f57::du-an-source-code-csharp-asp-net.cpp">Dự án &amp; Source code C#, ASP.NET</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f58::cong-cu-ebooks-csharp-asp-net-windows-mobile.cpp">Công cụ, ebooks C#, ASP.NET, và Windows Mobile</a></li>
			
		
			
					</ol>
				</li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f10::lap-trinh-objective-c.cpp">LẬP TRÌNH OBJECTIVE-C</a>
					<ol class="d1">
						
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f40::nhap-mon-lap-trinh-objective-c.cpp">Nhập môn lập trình Objective-C</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f68::thac-mac-iphone-ipad-mac-os-x.cpp">Thắc mắc IPhone, IPad, Mac OS X</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f41::thac-mac-lap-trinh-objective-c.cpp">Thắc mắc lập trình Objective-C</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f48::tutorials-thu-thuat-lap-trinh-objective-c.cpp">Tutorials và Thủ thuật lập trình Objective-C</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f65::cong-cu-tai-lieu-lap-trinh-objective-c.cpp">Công cụ, Tài liệu lập trình Objective-C</a></li>
			
		
			
					</ol>
				</li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f11::lap-trinh-java.cpp">LẬP TRÌNH JAVA</a>
					<ol class="d1">
						
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f71::thac-mac-lap-trinh-java.cpp">Thắc mắc lập trình Java</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f72::lap-trinh-android-java-mobile.cpp">Lập trình Android và Java Mobile</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f73::tutorials-thu-thuat-lap-trinh-java.cpp">Tutorials và Thủ thuật lập trình Java</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f74::du-an-source-code-java.cpp">Dự án &amp; Source code Java</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f75::cong-cu-ebooks-java.cpp">Công cụ, ebooks Java</a></li>
			
		
			
					</ol>
				</li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f5::lap-trinh-visual-cpp-lap-trinh-visual-cpp-net.cpp">LẬP TRÌNH VISUAL C++ | LẬP TRÌNH VISUAL C++.NET</a>
					<ol class="d1">
						
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f14::thac-mac-lap-trinh-visual-cpp.cpp">Thắc mắc lập trình Visual C++</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f61::windows-api-hooking-xu-ly-windows-message.cpp">Windows API, Hooking, xử lý Windows Message</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f38::lap-trinh-virus-anti-virus.cpp">Lập trình Virus &amp; Anti-Virus</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f30::tutorials-thu-thuat-visual-cpp.cpp">Tutorials và Thủ thuật Visual C++</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f64::du-an-source-code-visual-cpp.cpp">Dự án &amp; Source code VC++</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f66::cong-cu-ebooks-visual-cpp.cpp">Công cụ, ebooks VC++</a></li>
			
		
			
					</ol>
				</li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f7::lap-trinh-cpp-lap-trinh-c-lap-trinh-cpp0x.cpp">LẬP TRÌNH C++ | LẬP TRÌNH C | LẬP TRÌNH C++0X</a>
					<ol class="d1">
						
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f59::thac-mac-lap-trinh-c-cpp-cpp0x.cpp">Thắc mắc lập trình C/C++/C++0x</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f36::thac-mac-ctdl-giai-thuat.cpp">Thắc mắc CTDL &amp; Giải thuật</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f27::thao-luan-gop-y-code-c-cpp-cua-ban.cpp">Thảo luận, góp ý code C/C++ của bạn</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f21::thu-thuat-tutorials-ma-nguon-c-cpp-cpp0x.cpp">Thủ thuật, Tutorials và Mã nguồn C/C++/C++0x</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f56::thu-thuat-tutorials-ctdl-giai-thuat.cpp">Thủ thuật, Tutorials CTDL &amp; Giải thuật</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f63::tai-lieu-ebooks-cong-cu.cpp">Tài liệu, ebooks và công cụ</a></li>
			
		
			
					</ol>
				</li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f16::lap-trinh-tren-linux-linux-programming.cpp">LẬP TRÌNH TRÊN LINUX | LINUX PROGRAMMING</a>
					<ol class="d1">
						
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f18::thac-mac-lap-trinh-shell-linux.cpp">Thắc mắc  lập trình shell Linux</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f23::thac-mac-lap-trinh-c-cpp-tren-linux.cpp">Thắc mắc lập trình C/C++ trên Linux</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f20::thu-thuat-tutorials-ma-nguon.cpp">Thủ thuật, Tutorials và Mã nguồn</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f24::cong-cu-tai-lieu-lap-trinh-tren-linux.cpp">Công cụ, Tài liệu lập trình trên Linux</a></li>
			
		
			
					</ol>
				</li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f12::database-reporting-cac-he-quan-tri-database.cpp">DATABASE &amp; REPORTING | CÁC HỆ QUẢN TRỊ DATABASE</a>
					<ol class="d1">
						
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f6::thac-mac-dai-cuong-database-reporting.cpp">Thắc mắc đại cương Database &amp; Reporting</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f35::thac-mac-oracle.cpp">Thắc mắc Oracle</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f60::thac-mac-microsoft-sql-server-microsoft-access.cpp">Thắc mắc Microsoft SQL Server &amp; Microsoft Access</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f34::thac-mac-mysql-sqlite.cpp">Thắc mắc MySQL và SQLite</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f67::thu-thuat-tutorials-database.cpp">Thủ thuật, Tutorials Database</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f39::tai-lieu-ebooks-db.cpp">Tài liệu, ebooks DB</a></li>
			
		
			
					</ol>
				</li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f22::thanh-vien-cong-dong-c-viet.cpp">THÀNH VIÊN CỘNG ĐỒNG C VIỆT</a>
					<ol class="d1">
						
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f51::hinh-tuong-thanh-vien.cpp">Hình tượng thành viên</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f28::y-tuong-san-pham-cntt-cua-ban.cpp">Ý tưởng sản phẩm CNTT của bạn</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f29::san-pham-phan-mem-cua-ban.cpp">Sản phẩm phần mềm của bạn</a></li>
			
		
			
					</ol>
				</li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f8::thao-luan-chung.cpp">THẢO LUẬN CHUNG</a>
					<ol class="d1">
						
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f13::thac-mac-chung.cpp">Thắc mắc chung</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f25::english-for-it-tieng-anh-cho-dan-cntt.cpp">English for IT | Tiếng anh cho dân CNTT</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f37::software-phan-mem-ebooks.cpp">Software (Phần mềm) | Ebooks</a></li>
			
		
			
					</ol>
				</li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f42::chuyen-muc-giai-tri.cpp">CHUYÊN MỤC GIẢI TRÍ</a>
					<ol class="d1">
						
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f43::giao-luu-chem-gio.cpp">Giao lưu - Chém gió</a></li>
			
		
			
				<li><a href="http://diendan.congdongcviet.com/forums/f33::giai-tri-thu-gian.cpp">Giải trí - Thư giãn</a></li>
			
		
			
					</ol>
				</li>
			
		
	</ul>
</div></div>

<div style="clear: left">
  
  <div id="ad_global_above_footer"><div style="height: 90px;">
<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
<!-- CViet Footer -->
<ins class="adsbygoogle"
     style="display:block"
     data-ad-client="ca-pub-2525409910423371"
     data-ad-slot="5681541683"
     data-ad-format="auto"></ins>
<script>
(adsbygoogle = window.adsbygoogle || []).push({});
</script>
</div></div>
</div>

<div id="footer" class="footer clearfix">
	<form action="http://diendan.congdongcviet.com/forum.php" method="get" id="footer_select" class="footer_select">
		
			<select name="styleid" onchange="switch_id(this, 'style')">
				<optgroup label="Chọn nhanh Style"><option class="hidden"></option></optgroup>
				
					
					<optgroup label="&nbsp;Standard Styles">
									
					

	<option value="4" class="" selected="selected">-- Computer Style</option>

					
					</optgroup>
										
				
				
					
					<optgroup label="&nbsp;Mobile Styles">
					
					

	<option value="5" class="" >-- Mobile Style</option>

					
					</optgroup>
					
				
			</select>	
		
		
		
	</form>

	<ul id="footer_links" class="footer_links">
		<li><a href="sendmessage.php" rel="nofollow" accesskey="9">Liên hệ chúng tôi</a></li>
		<li><a title="Cộng đồng C Việt" href="http://congdongcviet.com">Cộng đồng C Việt</a></li>
		
		
		<li><a href="archive/index.php">Archive</a></li>
		
		
		
		<li><a href="attachment.php?attachmentid=5373&amp;stc=1&amp;d=1299055314#top" onclick="document.location.hash='top'; return false;">Top</a></li>
	</ul>
	
	<script type="text/javascript">
	<!--
		// Main vBulletin Javascript Initialization
		vBulletin_init();
	//-->
	</script>
	
<script type="text/javascript">
	(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
	(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
	m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
	})(window,document,'script','//www.google-analytics.com/analytics.js','ga');
	
	ga('create', 'UA-6069265-2', 'congdongcviet.com');
	ga('send', 'pageview');
</script>
	<script language="javascript" type="text/javascript" src="http://diendan.congdongcviet.com/clientscript/cviet_avim.js"></script>
	<script language="javascript" type="text/javascript" src="http://diendan.congdongcviet.com/clientscript/cviet_bbcode.js"></script>
</div>
</div> <!-- closing div for body_wrapper -->

<div class="below_body">
<div id="footer_time" class="shade footer_time">Toàn bộ thời gian tính theo múi GMT +7. Bây giờ là <span class="time">10:14 AM</span>.</div>

<div id="footer_copyright" class="shade footer_copyright">
	<!-- Do not remove this copyright notice -->
	- Sáng lập bởi Kevin Hoang @2006<br />- Nguồn đã được cung cấp bởi vBulletin&reg; 4.2.2<br />- Bản quyền nguồn &copy;2018 vBulletin Solutions, Inc
	<!-- Do not remove this copyright notice -->	
</div>
<div id="footer_morecopyright" class="shade footer_morecopyright">
	<!-- Do not remove cronimage or your scheduled tasks will cease to function -->
	
	<!-- Do not remove cronimage or your scheduled tasks will cease to function -->
	- Sử dụng và phát triển bởi <a href="http://www.congdongcviet.com" title="Cộng đồng C Việt">Cộng đồng C Việt&reg;</a>: 2006 - 2014<br />
	
</div>


</div>
<script type="text/javascript" src="http://www.google.com.vn/coop/cse/brand?form=cse-search-box&amp;lang=vi"></script>
</body>
</html>