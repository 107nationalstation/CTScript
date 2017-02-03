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
var bgSprite = new Sprite();
bgSprite.width = game_width;
bgSprite.height = game_height;
bgSprite.interactive = true;


// dialog
var graphics = new PIXI.Graphics();
graphics.lineStyle(2, 0xFF00FF, 1);
graphics.beginFill(0xFF00BB, 0.5);
graphics.drawRoundedRect(5, game_height - dialog_height, dialog_width - 10 , dialog_height - 5 , 15);
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
var word = new Text('click' , style);
word.x = person.x + 30;
word.y = person.y + 40;


//character
var leftCharacter , middleCharacter , rightCharacter;
var leftCharacterSprite = new Sprite();
var middleCharacterSprite = new Sprite();
var rightCharacterSprite = new Sprite();

//video
//var vtexture = new VideoBaseTexture();
//var vvtexture = new PIXI.Texture();
var vsprite = new Sprite();
vsprite.width = game_width;
vsprite.height = game_height;

//control layerr
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
option_visible(false);

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
	index : 1,
	vis : false,
	sons : new Array()
};
Vtree[1] = node1;
node1.sons.push(2);
var node2 = {
	type : 'bg' ,
	index : 2,
	vis : false,
	value : 'bg/島_坂道_差分(夕方).jpg' ,
	sons : new Array()
};
Vtree[2] = node2;
node2.sons.push(3);
var node3 = {
	type : 'middle' ,
	index : 3,
	vis : false,
	value : 'char/chrysoA_a.png' ,
	sons : new Array()
};
Vtree[3] = node3;
node3.sons.push(4);
var node4 = {
	type : 'dialog' ,
	index : 4,
	vis : false,
	person : '【 ??? 】' ,
	word : '「 ass we can 」' ,
	sons : new Array()
};
Vtree[4] = node4;
node4.sons.push(5);
var node5 = {
	type : 'option2' ,
	index : 5,
	vis : false,
	flag1 : 'flag1' ,
	flag2 : 'flag2' ,
	op1 : '肛' ,
	op2 : '不肛' ,
	sons : new Array()
};
Vtree[5] = node5;
node5.sons.push(6);
var node6 = {
	type : 'stop' ,
	index : 6,
	vis : false,
	sons : new Array()
};
Vtree[6] = node6;
node6.sons.push(7);
var node7 = {
	type : 'flag' ,
	index : 7,
	vis : false,
	value : 'flag1' ,
	sons : new Array()
};
Vtree[7] = node7;
node7.sons.push(8);
var node8 = {
	type : 'dialog' ,
	index : 8,
	vis : false,
	person : '【 ??? 】' ,
	word : '「 boy next door 」' ,
	sons : new Array()
};
Vtree[8] = node8;
node8.sons.push(9);
var node9 = {
	type : 'stop' ,
	index : 9,
	vis : false,
	sons : new Array()
};
Vtree[9] = node9;
node9.sons.push(10);
var node10 = {
	type : 'middle' ,
	index : 10,
	vis : false,
	value : 'clear' ,
	sons : new Array()
};
Vtree[10] = node10;
node10.sons.push(11);
var node11 = {
	type : 'bg' ,
	index : 11,
	vis : false,
	value : 'bg/図書館２階_隠し書庫_白黒.jpg' ,
	sons : new Array()
};
Vtree[11] = node11;
node11.sons.push(12);
var node12 = {
	type : 'dialog' ,
	index : 12,
	vis : false,
	person : '' ,
	word : '「 deep dark fantasy 」' ,
	sons : new Array()
};
Vtree[12] = node12;
node12.sons.push(13);
var node13 = {
	type : 'stop' ,
	index : 13,
	vis : false,
	sons : new Array()
};
Vtree[13] = node13;
node13.sons.push(14);
var node14 = {
	type : 'des' ,
	index : 14,
	vis : false,
	value : '菊花好痛' ,
	sons : new Array()
};
Vtree[14] = node14;
node14.sons.push(15);
var node15 = {
	type : '}' ,
	index : 15,
	vis : false,
	sons : new Array()
};
Vtree[15] = node15;
node6.sons.push(16);
var node16 = {
	type : 'flag' ,
	index : 16,
	vis : false,
	value : 'flag2' ,
	sons : new Array()
};
Vtree[16] = node16;
node16.sons.push(17);
var node17 = {
	type : 'middle' ,
	index : 17,
	vis : false,
	value : 'char/chrysoB_g.png' ,
	sons : new Array()
};
Vtree[17] = node17;
node17.sons.push(18);
var node18 = {
	type : 'dialog' ,
	index : 18,
	vis : false,
	person : '【 ??? 】' ,
	word : '「 interesting 」' ,
	sons : new Array()
};
Vtree[18] = node18;
node18.sons.push(19);
var node19 = {
	type : '}' ,
	index : 19,
	vis : false,
	sons : new Array()
};
Vtree[19] = node19;
node6.sons.push(20);
var node20 = {
	type : 'stop' ,
	index : 20,
	vis : false,
	sons : new Array()
};
Vtree[20] = node20;
var gao;
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
			loader.add(now.value).load(function(){
				leftCharacterSprite.visible = true;
				leftCharacterSprite.texture = TextureCache[now.value];
				var source = leftCharacterSprite.texture.baseTexture.source;
			});
		}
	}
	else if(now.type == "middle"){
		if(now.value == "clear") middleCharacterSprite.visible = false;
		else{
			loader.add(now.value).load(function(){
				middleCharacterSprite.visible = true;
				middleCharacterSprite.texture = TextureCache[now.value];
				var source = middleCharacterSprite.texture.baseTexture.source;
				middleCharacterSprite.x = (game_width - source.width) / 2;
			});
		}
	}
	else if(now.type == "right"){
		if(now.value == "clear") rightCharacterSprite.visible = false;
		else{
			loader.add(now.value).load(function(){
				rightCharacterSprite.visible = true;
				rightCharacterSprite.texture = TextureCache[now.value];
				var source = rightCharacterSprite.texture.baseTexture.source;
				rightCharacterSprite.x = (game_width - source.width);
			});
		}
	}
	else if(now.type == "dialog"){
		person.text = now.person;
				
		word.text = now.word;
	}
	else if(now.type == "des"){
		person.text = '';
		
		word.text = now.value;
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
stage.addChild(middleCharacterSprite);
stage.addChild(rightCharacterSprite);
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
