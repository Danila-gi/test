export let eventsManager = {
    bind: [],
    action: [],
    actions :{
        space: false,
        arrowRight: false,
        arrowLeft: false,
    },
    setup: function(){
        this.bind[39] = 'runRight';
        this.bind[37] = 'runLeft';
        this.bind[38] = 'lookUp';
        this.bind[32] = 'jump';
        this.bind[83] = 'fire';
        document.body.addEventListener("keydown", this.onKeyDown);
        document.body.addEventListener("keyup", this.onKeyUp);
    },
    onKeyDown: function(event){
        let action = eventsManager.bind[event.keyCode];
        if (action){
            eventsManager.action[action] = true;
        }
    },
    onKeyUp: function(event){
        let action = eventsManager.bind[event.keyCode];
        if (action){
            eventsManager.action[action] = false;
        }
    }
};