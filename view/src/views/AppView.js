import ProcessView from './process/ProcessView'
import ExpandedForm from './ExpandedForm';

export const AppView = ({data, totals}) => {

  return (
      <div>
          <ExpandedForm title={data.name + " (збігів за патерном: " + data.pids.length +")"}>
          {data.pids.length === 0 ? 
            <div>Не знайдено</div>
            :
            <div>
            {data.pids.map((process) => <ProcessView data={process} totals={totals} />)}
            </div>
          }
          </ExpandedForm>
      </div>
  );
};

export default AppView;