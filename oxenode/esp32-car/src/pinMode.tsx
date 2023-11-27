import { ContentProps, TriggerProps, port } from "@oxenode/core";
import { NumberInput, Select } from "@oxenode/ui";

export const Name = "Pin Mode";

export default function Content({ node }: ContentProps) {
    return <>
        <h3>Pin Mode</h3>
        <span className="xsmall">Write digital state to pins</span>

        <NumberInput
            nodeId={node.id}
            name='gpioPin'
            value='12'
        />

        <Select
            nodeId={node.id}
            name='mode'
            value='1'
        >
            <option value={(0)}>Disable</option>
            <option value={(1 << 0)}>Input</option>
            <option value={(1 << 1)}>Output</option>
            <option value={(1 << 1) | (1 << 2)}>Output OD</option>
            <option value={(1 << 0) | (1 << 1) | (1 << 2)}>Input Output OD</option>
            <option value={(1 << 0) | (1 << 1)}>Input Output</option>
        </Select>

        { node.State.err && <>
            <span style={{ margin: '0.25rem', color: 'var(--red)'}}>
                {node.State.err}
            </span>
        </> }
    </>;
}

export function Trigger({ node, controller, inputs: { socket }, state: { mode, gpioPin } }: TriggerProps) {

    const commandBuffer = new Uint8Array([
        0x7F,           // GPIO Control
        gpioPin,        // GPIO Pin
        +mode & 0x07    // Forward
    ]);

    if (socket) socket.send(commandBuffer);
    else {
        node.State.err = 
            `Socket is not connected...`;

        controller.update(node);

        return controller.trigger(0);
    }

    return controller.trigger(0);
} 

export const ports = [
    port.input().type('trigger'),
    port.input().type('data').label('socket'),
    port.output().type('trigger'),
]