
import SystemView from './system/SystemView'
import AppView from './AppView';
import ExpandedForm from './ExpandedForm';

export const SourceView = ({title, data}) => {

    const totals = {
        cpu: Object.values(data.system.cpu).reduce((total, currentValue) => total + currentValue, 0), 
        memory: data.system.memory.main.total,
        swap: data.system.memory.swap.total,
    }

    const processes_items = data.processes.map((process, id) => 
        <AppView key={process.name} data={process} totals={totals}/>
    )

    return (
        <ExpandedForm title={title}>
            <ExpandedForm title={"System"}>
                <SystemView data={data.system} totals={totals} />
            </ExpandedForm>
            {processes_items}
        </ExpandedForm>
    );
};

export default SourceView;