var e={d:(t,n)=>{for(var r in n)e.o(n,r)&&!e.o(t,r)&&Object.defineProperty(t,r,{enumerable:!0,get:n[r]})},o:(e,t)=>Object.prototype.hasOwnProperty.call(e,t)},t={};e.d(t,{VG:()=>i,xz:()=>d,ZP:()=>a,Tt:()=>s});const n=window.OxenodeCore,r=window.OxenodeUi,o=window.jsxRuntimeExports;var i="Pin Mode";function a(e){var t=e.node;return(0,o.jsxs)(o.Fragment,{children:[(0,o.jsx)("h3",{children:"Pin Mode"}),(0,o.jsx)("span",{className:"xsmall",children:"Write digital state to pins"}),(0,o.jsx)(r.NumberInput,{nodeId:t.id,name:"gpioPin",value:"12"}),(0,o.jsxs)(r.Select,{nodeId:t.id,name:"mode",value:"1",children:[(0,o.jsx)("option",{value:0,children:"Disable"}),(0,o.jsx)("option",{value:1,children:"Input"}),(0,o.jsx)("option",{value:2,children:"Output"}),(0,o.jsx)("option",{value:6,children:"Output OD"}),(0,o.jsx)("option",{value:7,children:"Input Output OD"}),(0,o.jsx)("option",{value:3,children:"Input Output"})]}),t.State.err&&(0,o.jsx)(o.Fragment,{children:(0,o.jsx)("span",{style:{margin:"0.25rem",color:"var(--red)"},children:t.State.err})})]})}function d(e){var t=e.node,n=e.controller,r=e.inputs.socket,o=e.state,i=o.mode,a=o.gpioPin,d=new Uint8Array([127,a,7&+i]);return r?(r.send(d),n.trigger(0)):(t.State.err="Socket is not connected...",n.update(t),n.trigger(0))}var s=[n.port.input().type("trigger"),n.port.input().type("data").label("socket"),n.port.output().type("trigger")],p=t.VG,l=t.xz,u=t.ZP,c=t.Tt;export{p as Name,l as Trigger,u as default,c as ports};