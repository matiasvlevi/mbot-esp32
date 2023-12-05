import { ContentProps, TriggerProps, port } from "@oxenode/core";
import { NumberInput, Select } from "@oxenode/ui";

export const Name = "Motor";

export default function Content({ node }: ContentProps) {
    return <>
        <h3>Motor</h3>
        <span className="xsmall">Control motors</span>

        <Select
            nodeId={node.id}
            name='mode'
            value='1'
        >
            <option value="1">Go Forward</option>
            <option value="2">Turn Left</option>
            <option value="3">Turn Right</option>
            <option value="4">Brake</option>
        </Select>

        <NumberInput
            nodeId={node.id}
            name='speed'
            value='50'
        />

        { node.State.err && <>
            <span style={{ margin: '0.25rem', color: 'var(--red)'}}>
                {node.State.err}
            </span>
        </> }
    </>;
}

export async function Trigger({ node, controller, inputs: { socket }, state: { mode, speed } }: TriggerProps) {

    let motor_right, motor_left;
    switch(mode) {
        case '1':{
            motor_right = new Uint8Array([ speed ]);
            motor_left = new Uint8Array([ speed ]);
            break;
        }
        case '2':{
            motor_right = new Uint8Array([ -speed ]);
            motor_left = new Uint8Array([ speed ]);
            break;
        }
        case '3':{
            motor_right = new Uint8Array([ speed ]);
            motor_left = new Uint8Array([ -speed ]);
            break;
        }
        case '4':{
            motor_right = new Uint8Array([ 0 ]);
            motor_left = new Uint8Array([ 0 ]);
            break;
        }
    }

    const commandBuffer = new Uint8Array([
        0xC0,        // Motor Control
        ...motor_right,
        ...motor_left
    ]);

    console.log(commandBuffer);
    
    if (socket) socket.send(commandBuffer);
    else {
        node.State.err = 
            `Socket is not connected...`;

        controller.update(node);

        return controller.trigger(0);
    }

    const response = await (new Promise(r => {
        socket.onmessage = (data: string) => {
            r(data);
        };
    }));

    // TODO: handle the response from the device
    console.log(response);

    return controller.trigger(0);
} 

export const ports = [
    port.input().type('trigger'),
    port.input().type('data').label('socket'),
    port.output().type('trigger'),
]