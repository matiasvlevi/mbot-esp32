var e={d:(t,r)=>{for(var n in r)e.o(r,n)&&!e.o(t,n)&&Object.defineProperty(t,n,{enumerable:!0,get:r[n]})},o:(e,t)=>Object.prototype.hasOwnProperty.call(e,t)},t={};e.d(t,{VG:()=>i,xz:()=>s,ZP:()=>a,Tt:()=>d});const r=window.OxenodeCore,n=window.OxenodeUi,o=window.jsxRuntimeExports;var i="Write Pin";function a(e){var t=e.node;return(0,o.jsxs)(o.Fragment,{children:[(0,o.jsx)("h3",{children:"Write Pin"}),(0,o.jsx)("span",{className:"xsmall",children:"Write digital state to pins"}),(0,o.jsx)(n.NumberInput,{nodeId:t.id,name:"gpioPin",value:"12"}),(0,o.jsxs)(n.Select,{nodeId:t.id,name:"mode",value:"1",children:[(0,o.jsx)("option",{value:"1",children:"HIGH"}),(0,o.jsx)("option",{value:"0",children:"LOW"})]}),t.State.err&&(0,o.jsx)(o.Fragment,{children:(0,o.jsx)("span",{style:{margin:"0.25rem",color:"var(--red)"},children:t.State.err})})]})}function s(e){var t=e.node,r=e.controller,n=e.inputs.socket,o=e.state,i=o.mode,a=o.gpioPin,s=new Uint8Array([128,a,1&+i]);if(!n)return t.State.err="Socket is not connected...",r.update(t),r.trigger(0);n.send(s);var d=new Promise((function(e){n.onmessage=function(t){e(t)}}));return r.setCache("data",d),r.trigger(0)}var d=[r.port.input().type("trigger"),r.port.input().type("data").label("socket"),r.port.output().type("trigger")],l=t.VG,c=t.xz,p=t.ZP,u=t.Tt;export{l as Name,c as Trigger,p as default,u as ports};