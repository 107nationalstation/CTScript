//Author: hd7771

var loader = PIXI.loader,
	Container = PIXI.Container,
	autoDetectRenderer = PIXI.autoDetectRenderer,
	resources = PIXI.loader.resources,
    fromImage = PIXI.Texture.fromImage,
    Text = PIXI.Text,
    Sprite = PIXI.Sprite,
    Graphics = PIXI.Graphics,
    TextureCache = PIXI.utils.TextureCache,
    fromVideo = PIXI.VideoBaseTexture.fromUrls,
    VideoBaseTexture = PIXI.VideoBaseTexture;


var game_width = 1280 , game_height = 720 , dialog_width = 1280 , dialog_height = 185;

var renderer = PIXI.autoDetectRenderer(game_width, game_height, { antialias: true } , {backgroundColor : 0x1099bb} , { transparent: true });

//DOM
var gameArea = document.getElementById("gameArea");
gameArea.appendChild(renderer.view);
$('#gameArea').bind('contextmenu', function(e){
    return false;
});


// create the root of the scene graph
var stage = new Container();
stage.interactive = true;


// CG or BG
//var bgTexture = fromImage('bg/白.jpg');
var bgSprite = new Sprite();
bgSprite.width = game_width;
bgSprite.height = game_height;
bgSprite.interactive = true;


// dialog
var graphics = new PIXI.Graphics();
graphics.lineStyle(2, 0xFF00FF, 1);
graphics.beginFill(0xFF00BB, 0.5);
graphics.drawRoundedRect(5, game_height - dialog_height, dialog_width - 10, dialog_height - 5, 15);
graphics.endFill();
graphics.interactive = true;


//Text
//text_style
var style = {
    fontFamily : 'Arial',
    fontSize : '26px',
    fill : '#F7EDCA',
    stroke : '#4a1850',
    strokeThickness : 5,
    dropShadow : true,
    dropShadowColor : '#000000',
    dropShadowAngle : Math.PI / 6,
    dropShadowDistance : 0,
    wordWrap : true,
    wordWrapWidth : 440
};
style.fontSize = 26 + 'px';
//person_name
var person = new Text('' , style);
person.x = game_width / 6;
person.y = game_height - dialog_height;
//word
var word = new Text('' , style);
word.x = person.x + 30;
word.y = person.y + 40;


//character
var leftCharacter , middleCharacter , rightCharacter;
var leftCharacterSprite = new Sprite();
var middleCharacterSprite = new Sprite();
var rightCharacterSprite = new Sprite();
leftCharacterSprite.width = game_width / 2;
rightCharacterSprite.width = game_width / 2;
rightCharacterSprite.x = game_width / 2;
middleCharacterSprite.width = game_width / 2;
middleCharacterSprite.x = game_width / 4;
//video
//var vtexture = new VideoBaseTexture();
//var vvtexture = new PIXI.Texture();
var vsprite = new Sprite();
vsprite.width = game_width;
vsprite.height = game_height;

//control layer
var clickControl = new PIXI.Graphics();
clickControl.lineStyle(2, 0xFF00FF, 1);
clickControl.beginFill(0xFF00BB, 0);
clickControl.drawRoundedRect(0, 0, game_width, game_height, 15);
clickControl.endFill();
clickControl.interactive = true;
clickControl.on('mousedown' , onDown);
clickControl.on('touchstart' , onDown);
clickControl.on('rightdown' , onRight);

//option layer
var option1 = new PIXI.Graphics();
option1.lineStyle(2, 0xFF00FF, 1);
option1.beginFill(0xFF00BB, 0.5);
option1.drawRoundedRect(game_width / 4 , game_height / 6 , game_width / 2 , game_height / 18 , 30);
option1.endFill();
option1.interactive = true;
var option1_text = new Text('ass we can!!' , style);
option1_text.anchor.set(0.5 , 0.5);
option1_text.position.x = game_width / 2;
option1_text.position.y = game_height / 36 * 7;
option1_text.interactive = true;
//option1.visible = false;
//option1_text.visible = false;
var option1Control = new PIXI.Graphics();
option1Control.lineStyle(2, 0xFF00FF, 1);
option1Control.beginFill(0xFF00BB, 0);
option1Control.drawRoundedRect(game_width / 4 , game_height / 6 , game_width / 2 , game_height / 18 , 30);
option1Control.endFill();
option1Control.interactive = true;



var option2 = new PIXI.Graphics();
option2.lineStyle(2, 0xFF00FF, 1);
option2.beginFill(0xFF00BB, 0.5);
option2.drawRoundedRect(game_width / 4 , game_height / 6 + game_height / 18 + game_height / 36 , game_width / 2 , game_height / 18 , 30);
option2.endFill();
option2.interactive = true;
var option2_text = new Text('ass we can!!' , style);
option2_text.anchor.set(0.5 , 0.5);
option2_text.position.x = game_width / 2;
option2_text.position.y = game_height / 36 * 10;
option2_text.interactive = true;
//option2.visible = false;
//option2_text.visible = false;
var option2Control = new PIXI.Graphics();
option2Control.lineStyle(2, 0xFF00FF, 1);
option2Control.beginFill(0xFF00BB, 0);
option2Control.drawRoundedRect(game_width / 4 , game_height / 6 + game_height / 18 + game_height / 36 , game_width / 2 , game_height / 18 , 30);
option2Control.endFill();
option2Control.interactive = true;



option1Control.on('mouseover' , onButtonOver1).on('mouseout', onButtonOut1).on('mousedown', onButtonDown1);
option2Control.on('mouseover' , onButtonOver2).on('mouseout', onButtonOut2).on('mousedown', onButtonDown2);
var flag1 , flag2;
var opFlag = new Array();



function onButtonOver1()
{
	if(option1.visible == false) return;
	option1.clear();
	option1.lineStyle(2, 0x000000, 1);
	option1.beginFill(0x66ccff, 0.5);
	option1.drawRoundedRect(game_width / 4 , game_height / 6 , game_width / 2 , game_height / 18 , 30);
	option1.endFill();
}

function onButtonOut1()
{
	if(option1.visible == false) return;
	option1.clear();
	option1.lineStyle(2, 0xFF00FF, 1);
	option1.beginFill(0xFF00BB, 0.5);
	option1.drawRoundedRect(game_width / 4 , game_height / 6 , game_width / 2 , game_height / 18 , 30);
	option1.endFill();
}

function onButtonOver2()
{
	if(option2.visible == false) return;
	option2.clear();
	option2.lineStyle(2, 0x000000, 1);
	option2.beginFill(0x66ccff, 0.5);
	option2.drawRoundedRect(game_width / 4 , game_height / 6 + game_height / 18 + game_height / 36 , game_width / 2 , game_height / 18 , 30);
	option2.endFill();
}

function onButtonOut2()
{
	if(option2.visible == false) return;
	option2.clear();
	option2.lineStyle(2, 0xFF00FF, 1);
	option2.beginFill(0xFF00BB, 0.5);
	option2.drawRoundedRect(game_width / 4 , game_height / 6 + game_height / 18 + game_height / 36 , game_width / 2 , game_height / 18 , 30);
	option2.endFill();
}

function option_visible(val){
	option1.visible = val;
	option2.visible = val;
	option1_text.visible = val;
	option2_text.visible = val;
	option1Control.visible = val;
	option2Control.visible = val;
}

function onButtonDown1()
{
	option_visible(false);
	opFlag[flag1] = true;
	while(gaoStack[gaoCur - 1] == undefined) gaoCur --;
	if(gaoCur != 0) gaoStack[gaoCur - 1].next();
}

function onButtonDown2()
{
	option_visible(false);
	opFlag[flag2] = true;
	while(gaoStack[gaoCur - 1] == undefined) gaoCur --;
	if(gaoCur != 0) gaoStack[gaoCur - 1].next();
}

var Vtree = new Array();
var node1 = {
	type : 'init' ,
	index : 1 ,
	vis : false ,
	sons : new Array()
};
node1.sons.push(2);
var node2 = {
	type : 'bg' , 
	index : 2 , 
	value : 'bg/島_坂道_差分(夕方).jpg' ,
	vis : false ,
	sons : new Array()
};
node2.sons.push(3);
var node3 = {
	type : 'left' , 
	index : 3 ,
	value : 'char/chrysoA_a.png' ,
	vis : false ,
	sons : new Array()
};
node3.sons.push(4);
var node4 = {
	type : 'dialog' ,
	index : 4 , 
	person : '毛哥' ,
	word : 'fuck you' ,
	vis : false ,
	sons : new Array()
};
node4.sons.push(5);
var node5 = {
	type : 'stop' , 
	index : 5 , 
	vis : false ,
	sons : new Array()
};
node5.sons.push(6);
var node6 = {
	type : 'dialog' ,
	index : 6 ,
	person : '毛哥' , 
	word : 'ass we can' ,
	vis : false , 
	sons : new Array()
};
node6.sons.push(7);
node6.sons.push(8);
var node7 = {
	type : 'stop' , 
	index : 7 , 
	vis : false ,
	sons : new Array()
};
var node8 = {
	type : 'dialog' , 
	index : 8 , 
	person : '毛哥' , 
	word : 'fucking coming' ,
	vis : false , 
	sons : new Array()
};
node8.sons.push(9);
var node9 = {
	type : 'stop' , 
	index : 9 , 
	vis : false ,
	sons : new Array()
};
node9.sons.push(10);
var node10 = {
	type : 'flag' , 
	index : 10 , 
	value : 'flag1' ,
	vis : false , 
	sons : new Array()
}
node10.sons.push(11);
var node11 = {
	type : 'dialog' , 
	index : 11 , 
	person : '123' ,
	word : 'sample' , 
	vis : false ,
	sons : new Array()
}
node11.sons.push(12);
var node12 = {
	type : 'stop' ,
	index : 12 , 
	vis : false ,
	sons : new Array()
}
Vtree[1] = node1;
Vtree[2] = node2;
Vtree[3] = node3;
Vtree[4] = node4;
Vtree[5] = node5;
Vtree[6] = node6;
Vtree[7] = node7;
Vtree[8] = node8;
Vtree[9] = node9;
Vtree[10] = node10;
Vtree[11] = node11;
Vtree[12] = node12;


var gao;
//opFlag['flag1'] = true;
var gaoStack = Array();
var gaoCur = 0;
function *dfs(now){
	var flag = false;
	if(now.vis == true){
		
	}
	else if(now.type == "flag"){
		if(opFlag[now.value] == undefined || opFlag[now.value] == false){
			//var res = yield now.index;
			flag = true;
		}
	}
	else if(now.type == "bg"){
		bgSprite.texture = fromImage(now.value);
	}
	else if(now.type == "left"){
		if(now.value == "clear") leftCharacterSprite.visible = false;
		else{
			leftCharacterSprite.visible = true;
			leftCharacterSprite.texture = fromImage(now.value);
			var height = leftCharacterSprite.texture.baseTexture.source.height;
			var width = leftCharacterSprite.texture.baseTexture.source.width;
		}
	}
	else if(now.type == "middle"){
		if(now.value == "clear") middleCharacterSprite.visible = false;
		else{
			middleCharacterSprite.visible = true;
			middleCharacterSprite.texture = fromImage(now.value);
			var height = middleCharacterSprite.texture.baseTexture.source.height;
			var width = middleCharacterSprite.texture.baseTexture.source.width;
			middleCharacterSprite.x = (game_width - width) / 2;
		}
	}
	else if(now.type == "right"){
		if(now.value == "clear") rightCharacterSprite.visible = false;
		else{
			rightCharacterSprite.visible = true;
			rightCharacterSprite.texture = fromImage(now.value);
			var height = rightCharacterSprite.texture.baseTexture.source.height;
			var width = rightCharacterSprite.texture.baseTexture.source.width;
			rightCharacterSprite.x = game_width - width;
		}
	}
	else if(now.type == "dialog"){
		person.text = now.person;
				
		word.text = now.word;
	}
	else if(now.type == "stop"){
		yield now.index;
	}
	else if(now.type == "option2"){
		flag1 = now.flag1;
		flag2 = now.flag2;
		option1_text.text = now.op1;
		option2_text.text = now.op2;
		option_visible(true);
	}
	now.vis = true;
	if(!flag){
		for(var nxt = 0 ; nxt < now.sons.length ; ++ nxt){
			gaoStack[gaoCur ++] = yield* dfs(Vtree[now.sons[nxt]]);
		}
	}
}

gao = dfs(Vtree[1]);
gaoStack[gaoCur ++] = gao;
var vtexture = vsprite.texture.baseTexture;
function onDown(eventData){
	if(option1.visible == true) return;
	if(vtexture.source == null || vtexture.source.ended == true){
		if(person.visible == false){
			person.visible = true;
			word.visible = true;
			graphics.visible = true;
		}
		else{
			while(gaoStack[gaoCur - 1] == undefined) gaoCur --;
			if(gaoCur != 0) gaoStack[gaoCur - 1].next();
		}
	}
}

/*function onDown(eventData){
	if(vtexture.source == null || vtexture.source.ended == true){
		if(person.visible == false){
			person.visible = true;
			word.visible = true;
			graphics.visible = true;
		}
		else{
			if(cur < end){
				if(opBg[cur] != '') bgSprite.texture = fromImage(opBg[cur]);
				
				person.text = opPerson[cur];
				
				word.text = opWord[cur];
				
				if(opLeftCharacter[cur] == "clear") leftCharacterSprite.visible = false;
				else if(opLeftCharacter[cur] != ''){
					leftCharacterSprite.visible = true;
					leftCharacterSprite.texture = fromImage(opLeftCharacter[cur]);
					var height = leftCharacterSprite.texture.baseTexture.source.height;
					var width = leftCharacterSprite.texture.baseTexture.source.width;
					leftCharacterSprite.height = height * leftCharacterSprite.width / width;
				}
				
				if(opRightCharacter[cur] == "clear") rightCharacterSprite.visible = false;
				else if(opRightCharacter[cur] != ''){
					rightCharacterSprite.visible = true;
					rightCharacterSprite.texture = fromImage(opRightCharacter[cur]);
					var height = rightCharacterSprite.texture.baseTexture.source.height;
					var width = rightCharacterSprite.texture.baseTexture.source.width;
					rightCharacterSprite.height = height * rightCharacterSprite.width / width;
				}
				
				if(opMiddleCharacter[cur] == "clear") middleCharacterSprite.visible = false;
				else if(opMiddleCharacter[cur] != ''){
					middleCharacterSprite.visible = true;
					middleCharacterSprite.texture = fromImage(opMiddleCharacter[cur]);
					var height = middleCharacterSprite.texture.baseTexture.source.height;
					var width = middleCharacterSprite.texture.baseTexture.source.width;
					middleCharacterSprite.height = height * middleCharacterSprite.width / width;
				}
				
				cur ++;
			}
			else{
				
			}
		}
	}
}*/

function onRight(eventData){
	if(option1.visible == true) return;
	if(vtexture.source == null || vtexture.source.ended == true){
		if(person.visible == true){
			person.visible = false;
			word.visible = false;
			graphics.visible = false;
		}
		else{
			person.visible = true;
			word.visible = true;
			graphics.visible = true;
		}
	}
}


// add childs to stage
stage.addChild(bgSprite);
stage.addChild(leftCharacterSprite);
stage.addChild(rightCharacterSprite);
stage.addChild(middleCharacterSprite);
stage.addChild(graphics);
stage.addChild(person);
stage.addChild(word);
stage.addChild(vsprite);
stage.addChild(clickControl)
stage.addChild(option1);
stage.addChild(option1_text);
stage.addChild(option2);
stage.addChild(option2_text);
stage.addChild(option1Control);
stage.addChild(option2Control);


// run the render loop
animate();
function animate() {
    renderer.render(stage);
    if(vtexture.source == null || vtexture.source.ended == true) vsprite.visible = false;
    requestAnimationFrame( animate );
}

